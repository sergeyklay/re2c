/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -ci --type-header cond_enum_05.h
enum YYCONDTYPE {
	yyca,
};


{
	YYCTYPE yych;
	switch (YYGETCONDITION()) {
	case yyca:
		goto yyc_a;
	}
/* *********************************** */
yyc_a:
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR++;
	{}
}

/* Generated by re2c */

enum YYCONDTYPE {
	yyca,
};
