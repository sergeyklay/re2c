/* Generated by re2c */
#line 1 "input10.re"

#line 5 "<stdout>"
{
	YYCTYPE yych;
	goto yy0;
	++YYCURSOR;
yy0:
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch(yych){
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'F':
	case 'G':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':	goto yy2;
	default:	goto yy4;
	}
yy2:
	++YYCURSOR;
#line 8 "input10.re"
	{ return 1; }
#line 31 "<stdout>"
yy4:
	++YYCURSOR;
#line 10 "input10.re"
	{ return -1; }
#line 36 "<stdout>"
}
#line 12 "input10.re"

