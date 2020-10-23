<#
.SYNOPSIS
    re2c test script

.DESCRIPTION
    .

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
    [Int16]$Threads = 0,
    [Switch]$Skeleton = $false,
    [Switch]$KeepTempFiles = $false,
    [String]$Re2c=".\re2c.exe"
)

function DetectCpuCount {
    if (-not (Test-Path env:CPUS)) {
        $env:CPUS = (Get-CimInstance -Class 'CIM_Processor').NumberOfLogicalProcessors
    }

    if (-not $env:CPUS) {
        $env:CPUS = 1
    }
}

function ExitWithCode {
    param (
        [Parameter(Mandatory=$true)] [Int] $Code
    )

    $host.SetShouldExit($Code)
    exit $Code
}

if ($Threads -le 0) {
    DetectCpuCount
    $Threads = $env:CPUS
}

if ($null -eq (Get-Command $Re2c -ErrorAction SilentlyContinue)) {
    throw "Cannot find re2c executable (${Re2c})."
}

Write-Host "Running in ${Threads} thread(s)"

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

# set include paths, relative to build directory
$IncPaths = ""
$CurrentDirectory = Get-Location
Get-ChildItem $TestBuildDir -Recurse |
    Where-Object { $_.PSIsContainer -eq $true } |
        ForEach-Object {
            Set-Location $TestBuildDir
            $RelativePath = Resolve-Path -Relative $_.FullName
            Set-Location $CurrentDirectory

            $IncPaths += " -I " + $RelativePath
        }

# add path to include directory (if relative, add "..\.\" to step out of test subdirectory)
if ([System.IO.Path]::IsPathRooted($TopSrcDir)) {
    $IncPaths += " -I " + $TopSrcDir
} else {
    $IncPaths += " -I ..\.\" + $TopSrcDir
}

$TestsPerThread = [math]::Floor($Tests.Count / $Threads + 1)
$Packs = @()
for ($i = 0; $i -lt $Threads; $i++) {
    $j1 = $i * $TestsPerThread
    $j2 = $j1 + $TestsPerThread - 1
    $Packs += ,($Tests[$j1..$j2])
}

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

    Write-Output "tests:" | Out-File -Encoding "ASCII" -Append $JobCtx.LogFile

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
            -replace '\$INPUT', ('"' + $outx + '"') `
            -replace '\$OUTPUT', ('"' + $outy + '"') `
            -replace '(--type-header )([^ ]*)', ('$1' + (Split-Path $outx) + '\' + '$2')

        # enable warnings globally
        $switches = "$switches -W --no-version --no-generation-date"

        # normal tests
        if (-not $JobCtx.Skeleton) {
            # TODO: Implement me
        } else {
            Remove-Item $outy -Force -ErrorAction Ignore

            $switches = "$switches --skeleton -Werror-undefined-control-flow"
            $parameters = "$incpaths $switches".Split(" ")

            & $JobCtx.Re2c $parameters 2>"$outy.stderr"

            $EndCurrent = Get-Date
            Write-Output "    $($JobCtx.Re2c) $incpaths $switches ($(($EndCurrent - $StartCurrent).TotalSeconds))" | Out-File `
                -Encoding "ASCII" -Append $JobCtx.LogFile
        }
    }

    # log results
    Write-Output "ran tests:   $RanTests"   | Out-File -Encoding "ASCII" -Append $JobCtx.LogFile
    Write-Output "hard errors: $HardErrors" | Out-File -Encoding "ASCII" -Append $JobCtx.LogFile
    Write-Output "soft errors: $SoftErrors" | Out-File -Encoding "ASCII" -Append $JobCtx.LogFile

    $End = Get-Date

    Write-Output "time:  $(($End - $Start).TotalSeconds)" | Out-File `
        -Encoding "ASCII" -Append $JobCtx.LogFile
}

function CountTests {
    [OutputType([Int])]
    param (
        [Parameter(Mandatory=$true)] [String] $File,
        [Parameter(Mandatory=$true)] [String] $Type
    )

    (Get-Content $Log | Select-String -Pattern "(?<=${Type}:\s+)\d+") |
        ForEach-Object { [Int]$_.Matches[0].Value }
}

$AllLogs = @()
$AllJobs = @()
for ($i = 0; $i -lt $Packs.Count; $i++) {
    $Log = Join-Path (Resolve-Path .) "$(Get-Date -UFormat '%y%m%d%H%M%S')_${i}.log"
    $AllLogs += $Log

    $JobCtx = New-Object -TypeName psobject
    $JobCtx | Add-Member -MemberType NoteProperty -Name Tests -Value $Packs[$i]
    $JobCtx | Add-Member -MemberType NoteProperty -Name IncPaths -Value $IncPaths
    $JobCtx | Add-Member -MemberType NoteProperty -Name Skeleton -Value $Skeleton
    $JobCtx | Add-Member -MemberType NoteProperty -Name LogFile -Value $Log
    $JobCtx | Add-Member -MemberType NoteProperty -Name TestsRoot `
        -Value (Resolve-Path $TestBuildDir).ToString()
    $JobCtx | Add-Member -MemberType NoteProperty -Name Re2c `
        -Value (Resolve-Path $Re2c).ToString()

    # Execute the jobs in parallel
    $Job = Start-Job $Function:RunPack -Name "Re2cJob$i" -ArgumentList $JobCtx
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

    # Remove-Item $Log -Force -ErrorAction Ignore
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
Write-Host "-----------------"
Write-Host "All:         $($Tests.Count)"
Write-Host "Ran:         $TotalRanTests"
Write-Host "Passed:      $($TotalRanTests - $TotalHardErrors - $TotalSoftErrors)"
Write-Host "Soft errors: $TotalSoftErrors"
Write-Host "Hard errors: $TotalHardErrors"
Write-Host "Total time:  $(($EndTesting - $StartTesing).TotalSeconds)"
Write-Host "-----------------"

if ($TotalHardErrors -gt 0) {
    Write-Host "FAILED"
    # ExitWithCode 1
} else {
    Write-Host "PASSED"
    # ExitWithCode 0
}
