/* Generated by re2c */
#line 1 "../../../benchmarks/submatch_dfa_aot/src/re2c/32__rep_cat_23_19_17.re"
#include <assert.h>
#include <stdlib.h>
#include "common.h"

#line 15 "../../../benchmarks/submatch_dfa_aot/src/re2c/common.re"


typedef struct taglist_t {
    struct taglist_t *pred;
    long dist;
} taglist_t;

typedef struct taglistpool_t {
    taglist_t *head;
    taglist_t *next;
    taglist_t *last;
} taglistpool_t;

typedef struct {
    char *buf;
    char *lim;
    char *cur;
    char *mar;
    char *tok;
    
    taglist_t *yyt1;
taglist_t *yyt2;
taglist_t *yyt3;
taglist_t *yyt4;
taglist_t *yyt5;
taglist_t *yyt6;

    taglistpool_t tlp;
    int eof;
} input_t;

static inline void taglistpool_clear(taglistpool_t *tlp, input_t *in)
{
    tlp->next = tlp->head;
    in->yyt1 = 0;
in->yyt2 = 0;
in->yyt3 = 0;
in->yyt4 = 0;
in->yyt5 = 0;
in->yyt6 = 0;

}

static inline void taglistpool_init(taglistpool_t *tlp)
{
    static const unsigned size = 1024 * 1024;
    tlp->head = (taglist_t*)malloc(size * sizeof(taglist_t));
    tlp->next = tlp->head;
    tlp->last = tlp->head + size;
}

static inline void taglistpool_free(taglistpool_t *tlp)
{
    free(tlp->head);
    tlp->head = tlp->next = tlp->last = NULL;
}

static inline void taglist(taglist_t **ptl, const char *b, const char *t, taglistpool_t *tlp)
{
#ifdef GROW_MTAG_LIST
    if (tlp->next >= tlp->last) {
        const unsigned size = tlp->last - tlp->head;
        taglist_t *head = (taglist_t*)malloc(2 * size * sizeof(taglist_t));
        memcpy(head, tlp->head, size * sizeof(taglist_t));
        free(tlp->head);
        tlp->head = head;
        tlp->next = head + size;
        tlp->last = head + size * 2;
    }
#else
    assert(tlp->next < tlp->last);
#endif
    taglist_t *tl = tlp->next++;
    tl->pred = *ptl;
    tl->dist = t - b;
    *ptl = tl;
}

#line 6 "../../../benchmarks/submatch_dfa_aot/src/re2c/include-eof/fill.re"


static inline int fill(input_t *in)
{
    size_t free;
    if (in->eof) return 1;

    free = in->tok - in->buf;
    assert(free > 0);

    memmove(in->buf, in->tok, in->lim - in->tok);
    in->lim -= free;
    in->cur -= free;
    in->mar -= free;
    in->tok -= free;
    

    in->lim += fread(in->lim, 1, free, stdin);
    in->lim[0] = 0;

    if (in->lim < in->buf + SIZE) {
        in->eof = 1;
    }

    return 0;
}

static inline void init_input(input_t *in)
{
    in->buf = (char*) malloc(SIZE + 1);
    in->lim = in->buf + SIZE;
    in->cur = in->lim;
    in->mar = in->lim;
    in->tok = in->lim;
    
    in->yyt1 = 0;
in->yyt2 = 0;
in->yyt3 = 0;
in->yyt4 = 0;
in->yyt5 = 0;
in->yyt6 = 0;

    taglistpool_init(&in->tlp);
    in->eof = 0;
    fill(in);
}


static inline void free_input(input_t *in)
{
    free(in->buf);
    taglistpool_free(&in->tlp);
}

static int lex(input_t *in, Output *out);

int main(int argc, char **argv)
{
    PRE;
    input_t in;
    Output out;

    init_input(&in);
    init_output(&out);

    switch (lex(&in, &out)) {
        case 0:  break;
        case 1:  fprintf(stderr, "*** %s: syntax error\n", argv[0]); break;
        case 2:  fprintf(stderr, "*** %s: yyfill error\n", argv[0]); break;
        default: fprintf(stderr, "*** %s: panic\n", argv[0]); break;
    }

    flush(&out);
    free_output(&out);
    free_input(&in);

    POST;
    return 0;
}


static const char *print(Output *out, const char *tok,
    const taglist_t *t1, const taglist_t *t2, const taglist_t *t3)
{
    if (!t1) return tok;

    const char *p0 = print(out, tok, t1->pred, t2->pred, t3->pred);
    const char *p1 = tok + t1->dist;
    const char *p2 = tok + t2->dist;
    const char *p3 = tok + t3->dist;

    outs(out, p0, p1);
    outc(out, '.');
    outs(out, p1, p2);
    outc(out, '.');
    outs(out, p2, p3);
    outc(out, ';');

    return p3;
}

static int lex(input_t *in, Output *out)
{
    taglist_t *t1 = NULL, *t2 = NULL, *t3 = NULL;

loop:
    in->tok = in->cur;

#line 196 "gen/re2c/32__rep_cat_23_19_17-eof-tdfa0.c"
{
	char yych;
	in->yyt3 = in->yyt6;
	taglist(&in->yyt3, in->tok, in->tok - 1, &in->tlp);
	in->yyt2 = in->yyt5;
	taglist(&in->yyt2, in->tok, in->tok - 1, &in->tlp);
	in->yyt1 = in->yyt4;
	taglist(&in->yyt1, in->tok, in->tok - 1, &in->tlp);
yyFillLabel3_0:
	yych = *in->cur;
	switch (yych) {
	case '\n':
		++in->cur;
		goto yy4;
	case 'a':
		++in->cur;
		goto yy6;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_0;
			goto yy67;
		}
		++in->cur;
		goto yy2;
	}
yy2:
yy3:
#line 32 "../../../benchmarks/submatch_dfa_aot/src/re2c/32__rep_cat_23_19_17.re"
	{ return 1; }
#line 226 "gen/re2c/32__rep_cat_23_19_17-eof-tdfa0.c"
yy4:
	t1 = in->yyt1;
	t2 = in->yyt2;
	t3 = in->yyt3;
#line 33 "../../../benchmarks/submatch_dfa_aot/src/re2c/32__rep_cat_23_19_17.re"
	{
        print(out, in->tok, t1, t2, t3);
        outc(out, '\n');
        taglistpool_clear(&in->tlp, in);
        goto loop;
    }
#line 238 "gen/re2c/32__rep_cat_23_19_17-eof-tdfa0.c"
yy6:
	in->mar = in->cur;
yyFillLabel3_1:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy7;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_1;
		}
		goto yy3;
	}
yy7:
yyFillLabel3_2:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy9;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_2;
		}
		goto yy8;
	}
yy8:
	in->cur = in->mar;
	goto yy3;
yy9:
yyFillLabel3_3:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy10;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_3;
		}
		goto yy8;
	}
yy10:
yyFillLabel3_4:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy11;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_4;
		}
		goto yy8;
	}
yy11:
yyFillLabel3_5:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy12;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_5;
		}
		goto yy8;
	}
yy12:
yyFillLabel3_6:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy13;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_6;
		}
		goto yy8;
	}
yy13:
yyFillLabel3_7:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy14;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_7;
		}
		goto yy8;
	}
yy14:
yyFillLabel3_8:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy15;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_8;
		}
		goto yy8;
	}
yy15:
yyFillLabel3_9:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy16;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_9;
		}
		goto yy8;
	}
yy16:
yyFillLabel3_10:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy17;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_10;
		}
		goto yy8;
	}
yy17:
yyFillLabel3_11:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy18;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_11;
		}
		goto yy8;
	}
yy18:
yyFillLabel3_12:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy19;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_12;
		}
		goto yy8;
	}
yy19:
yyFillLabel3_13:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy20;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_13;
		}
		goto yy8;
	}
yy20:
yyFillLabel3_14:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy21;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_14;
		}
		goto yy8;
	}
yy21:
yyFillLabel3_15:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy22;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_15;
		}
		goto yy8;
	}
yy22:
yyFillLabel3_16:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy23;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_16;
		}
		goto yy8;
	}
yy23:
yyFillLabel3_17:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy24;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_17;
		}
		goto yy8;
	}
yy24:
yyFillLabel3_18:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy25;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_18;
		}
		goto yy8;
	}
yy25:
yyFillLabel3_19:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy26;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_19;
		}
		goto yy8;
	}
yy26:
yyFillLabel3_20:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy27;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_20;
		}
		goto yy8;
	}
yy27:
yyFillLabel3_21:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy28;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_21;
		}
		goto yy8;
	}
yy28:
yyFillLabel3_22:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		taglist(&in->yyt4, in->tok, in->cur, &in->tlp);
		goto yy29;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_22;
		}
		goto yy8;
	}
yy29:
yyFillLabel3_23:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy30;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_23;
		}
		goto yy8;
	}
yy30:
yyFillLabel3_24:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy31;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_24;
		}
		goto yy8;
	}
yy31:
yyFillLabel3_25:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy32;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_25;
		}
		goto yy8;
	}
yy32:
yyFillLabel3_26:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy33;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_26;
		}
		goto yy8;
	}
yy33:
yyFillLabel3_27:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy34;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_27;
		}
		goto yy8;
	}
yy34:
yyFillLabel3_28:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy35;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_28;
		}
		goto yy8;
	}
yy35:
yyFillLabel3_29:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy36;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_29;
		}
		goto yy8;
	}
yy36:
yyFillLabel3_30:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy37;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_30;
		}
		goto yy8;
	}
yy37:
yyFillLabel3_31:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy38;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_31;
		}
		goto yy8;
	}
yy38:
yyFillLabel3_32:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy39;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_32;
		}
		goto yy8;
	}
yy39:
yyFillLabel3_33:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy40;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_33;
		}
		goto yy8;
	}
yy40:
yyFillLabel3_34:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy41;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_34;
		}
		goto yy8;
	}
yy41:
yyFillLabel3_35:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy42;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_35;
		}
		goto yy8;
	}
yy42:
yyFillLabel3_36:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy43;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_36;
		}
		goto yy8;
	}
yy43:
yyFillLabel3_37:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy44;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_37;
		}
		goto yy8;
	}
yy44:
yyFillLabel3_38:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy45;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_38;
		}
		goto yy8;
	}
yy45:
yyFillLabel3_39:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy46;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_39;
		}
		goto yy8;
	}
yy46:
yyFillLabel3_40:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy47;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_40;
		}
		goto yy8;
	}
yy47:
yyFillLabel3_41:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		taglist(&in->yyt5, in->tok, in->cur, &in->tlp);
		goto yy48;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_41;
		}
		goto yy8;
	}
yy48:
yyFillLabel3_42:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy49;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_42;
		}
		goto yy8;
	}
yy49:
yyFillLabel3_43:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy50;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_43;
		}
		goto yy8;
	}
yy50:
yyFillLabel3_44:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy51;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_44;
		}
		goto yy8;
	}
yy51:
yyFillLabel3_45:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy52;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_45;
		}
		goto yy8;
	}
yy52:
yyFillLabel3_46:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy53;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_46;
		}
		goto yy8;
	}
yy53:
yyFillLabel3_47:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy54;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_47;
		}
		goto yy8;
	}
yy54:
yyFillLabel3_48:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy55;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_48;
		}
		goto yy8;
	}
yy55:
yyFillLabel3_49:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy56;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_49;
		}
		goto yy8;
	}
yy56:
yyFillLabel3_50:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy57;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_50;
		}
		goto yy8;
	}
yy57:
yyFillLabel3_51:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy58;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_51;
		}
		goto yy8;
	}
yy58:
yyFillLabel3_52:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy59;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_52;
		}
		goto yy8;
	}
yy59:
yyFillLabel3_53:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy60;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_53;
		}
		goto yy8;
	}
yy60:
yyFillLabel3_54:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy61;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_54;
		}
		goto yy8;
	}
yy61:
yyFillLabel3_55:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy62;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_55;
		}
		goto yy8;
	}
yy62:
yyFillLabel3_56:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy63;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_56;
		}
		goto yy8;
	}
yy63:
yyFillLabel3_57:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy64;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_57;
		}
		goto yy8;
	}
yy64:
yyFillLabel3_58:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		taglist(&in->yyt6, in->tok, in->cur, &in->tlp);
		goto yy65;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_58;
		}
		goto yy8;
	}
yy65:
yyFillLabel3_59:
	yych = *in->cur;
	switch (yych) {
	case '\n':
		++in->cur;
		in->yyt1 = in->yyt4;
		in->yyt2 = in->yyt5;
		in->yyt3 = in->yyt6;
		goto yy4;
	case 'a':
		++in->cur;
		goto yy66;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_59;
		}
		goto yy8;
	}
yy66:
yyFillLabel3_60:
	yych = *in->cur;
	switch (yych) {
	case 'a':
		++in->cur;
		goto yy7;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_60;
		}
		goto yy8;
	}
yy67:
#line 5 "../../../benchmarks/submatch_dfa_aot/src/re2c/include-eof/fill.re"
	{ return 0; }
#line 1035 "gen/re2c/32__rep_cat_23_19_17-eof-tdfa0.c"
}
#line 39 "../../../benchmarks/submatch_dfa_aot/src/re2c/32__rep_cat_23_19_17.re"

}
