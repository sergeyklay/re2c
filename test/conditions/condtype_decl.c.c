/* Generated by re2c */
#line 1 "conditions/condtype_decl.c.re"
#line 4 "conditions/condtype_decl.c.c"
enum YYCONDTYPE {
	yyca,
	yycb,
};
#line 1 "conditions/condtype_decl.c.re"


int main ()
{
	YYCONDTYPE cond;
	char * YYCURSOR;
#define YYGETCONDITION() cond

#line 18 "conditions/condtype_decl.c.c"
{
	unsigned char yych;
	switch (YYGETCONDITION()) {
	case yyca:
		goto yyc_a;
	case yycb:
		goto yyc_b;
	}
/* *********************************** */
yyc_a:
	yych = *YYCURSOR;
	switch (yych) {
	case 'a':	goto yy3;
	default:	goto yy2;
	}
yy2:
yy3:
	++YYCURSOR;
#line 11 "conditions/condtype_decl.c.re"
	{}
#line 39 "conditions/condtype_decl.c.c"
/* *********************************** */
yyc_b:
	yych = *YYCURSOR;
	switch (yych) {
	case 'b':	goto yy8;
	default:	goto yy7;
	}
yy7:
yy8:
	++YYCURSOR;
#line 12 "conditions/condtype_decl.c.re"
	{}
#line 52 "conditions/condtype_decl.c.c"
}
#line 13 "conditions/condtype_decl.c.re"

	return 0;
}
conditions/condtype_decl.c.re:13:2: warning: control flow in condition 'a' is undefined for strings that match '[\x0-\x60\x62-\xFF]', use default rule '*' [-Wundefined-control-flow]
conditions/condtype_decl.c.re:13:2: warning: control flow in condition 'b' is undefined for strings that match '[\x0-\x61\x63-\xFF]', use default rule '*' [-Wundefined-control-flow]