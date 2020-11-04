<#
    .SYNOPSIS
        re2c test script.

    .DESCRIPTION
        A PowerShell wrapper to run re2c tests in parallel.

    .EXAMPLE
        .\run_tests.ps1 -Skeleton

        Run skeleton validation.

    .EXAMPLE
        .\run_tests.ps1 -Threads 20 -Re2c .\.build_msvc\Debug\re2c.exe

        Override CPU autodetection and specify the path to re2c
        executable.

    .PARAMETER Threads
        Override CPU autodetection and use specified value.

    .PARAMETER Skeleton
        Run skeleton validation for sources that support it.

    .PARAMETER KeepTempFiles
        Don't delete temporary files after test run.

    .PARAMETER Re2c
        Specifies a path to re2c executable.
#>

param (
    [UInt16] $Threads = 0,
    [Switch] $Skeleton = $false,
    [Switch] $KeepTempFiles = $false,
    [String] $Re2c=".\re2c.exe"
)

function DetectCpuCount {
    <#
        .SYNOPSIS
            Get CPU count.

        .DESCRIPTION
            This function is used to autodetect the number of logical
            processors by using CIM.

        .EXAMPLE
            $CPUs = DetectCpuCount
    #>
    return (Get-CimInstance -Class 'CIM_Processor').NumberOfLogicalProcessors
}

function ExitWithCode {
    <#
        .SYNOPSIS
            Stop current PowerShell script with a exit code.

        .DESCRIPTION
            This function is intended to immediately terminate the current
            PowerShell script with a particular exit code.

        .EXAMPLE
            ExitWithCode 1

        .PARAMETER Code
            Exit code.
    #>
    param (
        [Parameter(Mandatory=$true)] [UInt16] $Code
    )

    $host.SetShouldExit($Code)
    exit $Code
}

function CreatePacks {
    <#
        .SYNOPSIS
            Create test packs for parallel execution.

        .DESCRIPTION
            This function is intended to split the array of tests into a
            multidimensional array. Each element of the returned array is an
            array of tests to run on a single CPU core.

        .PARAMETER Tests
            Array of tests.

        .PARAMETER Threads
            Number of CPU cores to use.
    #>
    param (
        [Parameter(Mandatory=$true)] [String[]] $Tests,
        [Parameter(Mandatory=$true)] [UInt16] $Threads
    )

    $Packs = @()
    $TestsPerThread = [math]::Floor($Tests.Count / $Threads + 1)

    for ($i = 0; $i -lt $Threads; $i++) {
        $j1 = $i * $TestsPerThread
        $j2 = $j1 + $TestsPerThread - 1
        $Packs += ,($Tests[$j1..$j2])
    }

    return $Packs
}

function CreateIncludePaths {
    <#
        .SYNOPSIS
            Create include paths, relative to build directory.

        .DESCRIPTION
            Creates a list of include paths, which are used when searching for
            include files. All paths in that list will be relative to build
            directory except TopSrcDir if it was passed in absolute form.

        .PARAMETER TopTestsDir
            Base tests directory.

        .PARAMETER TopSrcDir
            Base project directory.
    #>
    param (
        [Parameter(Mandatory=$true)] [String] $TopTestsDir,
        [Parameter(Mandatory=$true)] [String] $TopSrcDir
    )

    $Paths = ""

    $CurrentLocation = Get-Location
    Set-Location $TopTestsDir

    Get-ChildItem . -Recurse |
            Where-Object { $_.PSIsContainer -eq $true } |
            ForEach-Object {
                $RelativePath = Resolve-Path -Relative $_.FullName
                $Paths += " -I " + $RelativePath
            }

    Set-Location $CurrentLocation

    if ([System.IO.Path]::IsPathRooted($TopSrcDir)) {
        $Paths += " -I " + $TopSrcDir
    } else {
        $Paths += " -I ..\.\" + $TopSrcDir
    }

    return $Paths
}

if ($Threads -eq 0) {
    $Threads = DetectCpuCount
}

if ($null -eq (Get-Command $Re2c -ErrorAction SilentlyContinue)) {
    throw "Cannot find re2c executable (${Re2c})."
}

Write-Output "Running in $Threads thread(s)"

$StartTesing = Get-Date
$TestBuildDir = ".\test_$(Get-Date -UFormat '%y%m%d%H%M%S')\"
# TODO: "Get-Location" => "@top_srcdir@"
$TopSrcDir = Get-Location

Remove-Item $TestBuildDir -Force -Recurse -ErrorAction Ignore
New-Item $TestBuildDir -ItemType "directory" | Out-Null

# preserve directory structure
# TODO: parse test files from command line like bash does
Copy-Item -Path "${TopSrcDir}\test\*" -Destination $TestBuildDir -Recurse -Force
Copy-Item -Path "${TopSrcDir}\examples\*" -Destination $TestBuildDir -Recurse -Force

$Exclude = @(".re", ".c", ".h", ".go", ".inc")
Get-ChildItem $TestBuildDir -Recurse |
    Where-Object { (-not $_.PSIsContainer) -and ($Exclude -notcontains $_.Extension) } |
        ForEach-Object {
            Remove-Item $_.FullName -Force -Recurse -ErrorAction Ignore
        }

# if not a debug build, remove all debug subdirs
$Re2cOutput = & $Re2c --version
if ($Re2cOutput -notmatch '(debug)') {
    Get-ChildItem $TestBuildDir -Recurse |
        Where-Object { $_.PSIsContainer -eq $true -and $_.Name -match "debug" } |
            ForEach-Object {
                Remove-Item $_.FullName -Force -Recurse -ErrorAction Ignore
            }
}

$Tests = Get-ChildItem $TestBuildDir -Filter *.re -Recurse |
    Sort-Object | ForEach-Object { $_.FullName }


function RunPack {
    param (
        [Parameter(Mandatory=$true)] [PSCustomObject] $JobCtx
    )

    $RanTests = 0
    $HardErrors = 0
    $SoftErrors = 0
    $Start = Get-Date

    New-Item $JobCtx.LogFile -ItemType "file" | Out-Null

    $TestsRoot = $JobCtx.TestsRoot.Trim('\') + '\'
    $RootLength = $TestsRoot.Length

    $JobCtx.Re2c | Add-Content $JobCtx.LogFile

    $JobCtx.Tests | ForEach-Object {
        Set-Location $TestsRoot
        $StartCurrent = Get-Date

        # remove prefix
        $outx = $_.Substring($RootLength)

        # generate file extension (.c for C/C++, .go for Go)
        $ext = if ((Get-Content $outx -First 1) -match "re2go") {"go"} else {"c"}
        $outy = $outx -replace '^(.*)\.re$', ('$1.' + $ext)

        $switches = (Get-Content $outx -First 1) `
            -replace 're2go', 're2c --lang go' `
            -replace '.*re2c (.*)$', '$1' `
            -replace '\$INPUT', "`"$outx`"" `
            -replace '\$OUTPUT', "`"$outy`"" `
            -replace '(--type-header )([^ ]*)', ('$1' + (Split-Path $outx) + '\' + '$2')

        # enable warnings globally
        $switches = "$switches -W --no-version --no-generation-date"

        # normal tests
        if (-not $JobCtx.Skeleton) {
            # TODO: Implement me
        } else {
            Remove-Item $outy -Force -ErrorAction Ignore

            $switches = "$switches --skeleton -Werror-undefined-control-flow"
            $parameters = "$($JobCtx.IncPaths) $switches".Split(" ")

            "    $parameters" | Add-Content $JobCtx.LogFile -NoNewline
            & $JobCtx.Re2c $parameters 2>"$outy.stderr"

            $EndCurrent = Get-Date
            $TotalTime = ($EndCurrent - $StartCurrent).TotalSeconds
            " ($TotalTime)" | Add-Content $JobCtx.LogFile
        }
    }

    # log results
    "ran tests:   $RanTests"   | Add-Content $JobCtx.LogFile
    "hard errors: $HardErrors" | Add-Content $JobCtx.LogFile
    "soft errors: $SoftErrors" | Add-Content $JobCtx.LogFile

    $End = Get-Date

    "time:  $(($End - $Start).TotalSeconds)" | Add-Content $JobCtx.LogFile
}

function CountTests {
    [OutputType([uint32])]
    param (
        [Parameter(Mandatory=$true)] [String] $File,
        [Parameter(Mandatory=$true)] [String] $Type
    )

    (Get-Content $Log | Select-String -Pattern "(?<=${Type}:\s+)\d+") |
        ForEach-Object { [UInt32]$_.Matches[0].Value }
}

$Packs = CreatePacks $Tests $Threads
$AllLogs = @()
$AllJobs = @()
for ($i = 0; $i -lt $Packs.Count; $i++) {
    $Log = Join-Path (Resolve-Path .) "$(Get-Date -UFormat '%y%m%d%H%M%S')_${i}.log"
    $AllLogs += $Log

    $JobCtx = New-Object -TypeName psobject
    $JobCtx | Add-Member -MemberType NoteProperty -Name Tests -Value $Packs[$i]
    $JobCtx | Add-Member -MemberType NoteProperty -Name IncPaths `
        -Value (CreateIncludePaths $TestBuildDir $TopSrcDir)
    $JobCtx | Add-Member -MemberType NoteProperty -Name Skeleton -Value $Skeleton
    $JobCtx | Add-Member -MemberType NoteProperty -Name LogFile -Value $Log
    $JobCtx | Add-Member -MemberType NoteProperty -Name TestsRoot `
        -Value (Resolve-Path $TestBuildDir).ToString()
    $JobCtx | Add-Member -MemberType NoteProperty -Name Re2c `
        -Value (Resolve-Path $Re2c).ToString()

    # Execute the jobs in parallel
    $Job = Start-Job $Function:RunPack -Name "re2c-$i" -ArgumentList $JobCtx
    $AllJobs += $Job
}

# Wait for it all to complete (if not done yet)
Wait-Job -Job $AllJobs -Timeout 60 | Out-Null

# Discard the jobs
Remove-Job -Job $AllJobs

$EndTesting = Get-Date
$TotalRanTests = 0
$TotalHardErrors = 0
$TotalSoftErrors = 0
for ($i = 0; $i -lt $AllLogs.Count; $i++) {
    $Log = $AllLogs[$i]

    $TotalRanTests += CountTests $Log "ran tests"
    $TotalHardErrors += CountTests $Log "hard errors"
    $TotalSoftErrors += CountTests $Log "soft errors"

    # TODO: Remove-Item $Log -Force -ErrorAction Ignore
}

# remove directories that are empty or contain only .inc, .h and .go files
Get-ChildItem $TestBuildDir -Recurse |
    Where-Object { $_.PSIsContainer -eq $true } | Sort-Object -Descending FullName |
        ForEach-Object {
            $Exclude = @(".inc", ".h", ".go", ".inc")
            $Files = Get-ChildItem $_.FullName -Recurse |
                Where-Object { (-not $_.PSIsContainer) -and ($Exclude -notcontains $_.Extension) }

            if ($Files.Count -eq 0) {
                Remove-Item $_.FullName -Force -Recurse -ErrorAction Ignore
            }
        }

# report results
Write-Output "-----------------"
Write-Output "All:         $($Tests.Count)"
Write-Output "Ran:         $TotalRanTests"
Write-Output "Passed:      $($TotalRanTests - $TotalHardErrors - $TotalSoftErrors)"
Write-Output "Soft errors: $TotalSoftErrors"
Write-Output "Hard errors: $TotalHardErrors"
Write-Output "Total time:  $(($EndTesting - $StartTesing).TotalSeconds)"
Write-Output "-----------------"

if ($TotalHardErrors -gt 0) {
    Write-Output "FAILED"
    # TODO: ExitWithCode 1
} else {
    Write-Output "PASSED"
    # TODO: ExitWithCode 0
}
