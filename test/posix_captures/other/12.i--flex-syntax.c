/* Generated by re2c */

{
	YYCTYPE yych;
	unsigned int yyaccept = 0;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *(YYMARKER = YYCURSOR);
	switch (yych) {
	case 'X':
		yyt1 = yyt3 = YYCURSOR;
		goto yy3;
	case 'Y':
		yyt1 = yyt3 = YYCURSOR;
		goto yy5;
	case 'a':
		yyt1 = yyt3 = YYCURSOR;
		goto yy7;
	case 'b':
		yyt1 = yyt3 = YYCURSOR;
		goto yy9;
	default:
		yyt2 = yyt3 = NULL;
		yyt1 = YYCURSOR;
		goto yy2;
	}
yy2:
	yynmatch = 2;
	yypmatch[0] = yyt1;
	yypmatch[2] = yyt2;
	yypmatch[3] = yyt3;
	yypmatch[1] = YYCURSOR;
	{}
yy3:
	yyaccept = 1;
	YYMARKER = ++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'X':
		yyt3 = YYCURSOR;
		goto yy3;
	case 'Y':
		yyt3 = YYCURSOR;
		goto yy5;
	case 'a':
		yyt4 = YYCURSOR;
		goto yy10;
	case 'b':
		yyt2 = yyt3;
		yyt3 = YYCURSOR;
		goto yy9;
	default:
		yyt2 = yyt3;
		yyt3 = YYCURSOR;
		goto yy2;
	}
yy5:
	yyaccept = 1;
	YYMARKER = ++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'X':
		yyt3 = YYCURSOR;
		goto yy3;
	case 'Y':
		yyt3 = YYCURSOR;
		goto yy5;
	case 'a':
		yyt2 = yyt3;
		yyt3 = YYCURSOR;
		goto yy7;
	case 'b':
		yyt2 = yyt3;
		yyt3 = YYCURSOR;
		goto yy9;
	default:
		yyt2 = yyt3;
		yyt3 = YYCURSOR;
		goto yy2;
	}
yy7:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'b':	goto yy11;
	default:	goto yy8;
	}
yy8:
	YYCURSOR = YYMARKER;
	switch (yyaccept) {
	case 0:
		yyt2 = yyt3 = NULL;
		yyt1 = YYCURSOR;
		goto yy2;
	case 1:
		yyt3 = YYCURSOR;
		goto yy2;
	case 2:
		yyt2 = yyt4;
		yyt3 = YYCURSOR;
		goto yy2;
	default:
		yyt2 = yyt5;
		yyt3 = YYCURSOR;
		goto yy2;
	}
yy9:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'Y':	goto yy5;
	case 'a':	goto yy12;
	default:	goto yy8;
	}
yy10:
	yyaccept = 1;
	YYMARKER = ++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'X':
		yyt3 = YYCURSOR;
		goto yy3;
	case 'Y':
		yyt3 = YYCURSOR;
		goto yy5;
	case 'a':
		yyt2 = yyt3;
		yyt3 = YYCURSOR;
		goto yy7;
	case 'b':
		yyt5 = YYCURSOR;
		goto yy13;
	default:
		yyt2 = yyt3;
		yyt3 = YYCURSOR;
		goto yy2;
	}
yy11:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'a':	goto yy14;
	default:	goto yy8;
	}
yy12:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'b':	goto yy15;
	default:	goto yy8;
	}
yy13:
	yyaccept = 1;
	YYMARKER = ++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'X':
		yyt3 = YYCURSOR;
		goto yy3;
	case 'Y':
		yyt3 = YYCURSOR;
		goto yy5;
	case 'a':
		yyt2 = YYCURSOR;
		goto yy16;
	case 'b':
		yyt2 = yyt3;
		yyt3 = YYCURSOR;
		goto yy9;
	default:
		yyt2 = yyt3;
		yyt3 = YYCURSOR;
		goto yy2;
	}
yy14:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'b':	goto yy5;
	default:	goto yy8;
	}
yy15:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'a':	goto yy5;
	default:	goto yy8;
	}
yy16:
	yyaccept = 1;
	YYMARKER = ++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'X':
		yyt3 = YYCURSOR;
		goto yy3;
	case 'Y':
		yyt3 = YYCURSOR;
		goto yy5;
	case 'a':
		yyt2 = yyt3;
		yyt3 = YYCURSOR;
		goto yy7;
	case 'b':
		yyt3 = YYCURSOR;
		goto yy17;
	default:
		yyt2 = yyt3;
		yyt3 = YYCURSOR;
		goto yy2;
	}
yy17:
	yyaccept = 2;
	YYMARKER = ++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'X':
		yyt3 = YYCURSOR;
		goto yy3;
	case 'Y':	goto yy5;
	case 'a':
		yyt4 = YYCURSOR;
		goto yy18;
	case 'b':
		yyt3 = YYCURSOR;
		goto yy9;
	default:
		yyt2 = yyt4;
		yyt3 = YYCURSOR;
		goto yy2;
	}
yy18:
	yyaccept = 3;
	YYMARKER = ++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'X':
		yyt3 = YYCURSOR;
		goto yy3;
	case 'Y':
		yyt3 = YYCURSOR;
		goto yy5;
	case 'a':
		yyt3 = YYCURSOR;
		goto yy7;
	case 'b':
		yyt5 = YYCURSOR;
		goto yy19;
	default:
		yyt2 = yyt5;
		yyt3 = YYCURSOR;
		goto yy2;
	}
yy19:
	yyaccept = 1;
	YYMARKER = ++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'X':
		yyt3 = YYCURSOR;
		goto yy3;
	case 'Y':
		yyt3 = YYCURSOR;
		goto yy5;
	case 'a':
		yyt2 = YYCURSOR;
		goto yy16;
	case 'b':
		yyt3 = YYCURSOR;
		goto yy9;
	default:
		yyt3 = YYCURSOR;
		goto yy2;
	}
}

posix_captures/other/12.i--flex-syntax.re:5:4: warning: rule matches empty string [-Wmatch-empty-string]
posix_captures/other/12.i--flex-syntax.re:6:7: warning: rule matches empty string [-Wmatch-empty-string]
posix_captures/other/12.i--flex-syntax.re:6:7: warning: unreachable rule (shadowed by rule at line 5) [-Wunreachable-rules]