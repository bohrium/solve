#include <stdio.h>
#include "expr.h"
#include "test_expr.h"

void test_clause()
{
    printf("TEST CLAUSE...\n");
    Clause c; construct_clause(&c);

    print_clause(&c); printf("\texpected ()\n");

    /* test insertion of positive literal */
    insert_var(&c, 1);
    print_clause(&c); printf("\texpected (A)\n");

    /* test second negative literal */
    insert_var(&c, -2);
    print_clause(&c); printf("\texpected (Ab)\n");

    /* test redundant insertion */
    insert_var(&c, 1);
    print_clause(&c); printf("\texpected (Ab)\n");

    /* test capacity expansion */
    insert_var(&c,-9); insert_var(&c, 5); insert_var(&c, 4); insert_var(&c,-8);
    print_clause(&c); printf("\texpected (AbiEDh)\n");

    /* test creation of tautology */
    insert_var(&c,-1);
    print_clause(&c); printf("\texpected T\n");

    /* test terminality of tautology */
    insert_var(&c,3);
    print_clause(&c); printf("\texpected T\n");

    destroy_clause(&c);
    printf("\n");
}

void test_cnf()
{
    printf("TEST CNF...\n");
    Clause ca; construct_clause(&ca);                     insert_var(&ca,-2); insert_var(&ca, 3); 
    Clause cb; construct_clause(&cb); insert_var(&cb, 9); insert_var(&cb,-9);
    Clause cc; construct_clause(&cc); insert_var(&cc,-8); insert_var(&cc, 3); insert_var(&cc,-9);
    Clause cd; construct_clause(&cd);                     insert_var(&cd, 3); insert_var(&cd,-2);
    Clause ce; construct_clause(&ce); insert_var(&ce, 1); insert_var(&ce,-2); insert_var(&ce, 3);
    Clause cf; construct_clause(&cf);                                         insert_var(&cf, 3);
    CNF f; construct_cnf(&f);

    print_cnf(&f); printf("\texpected [0:]\n");

    /* test insertion of non-tautology */
    insert_clause(&f, &ca);
    print_cnf(&f); printf("\texpected [3:(bC)]\n");

    /* test insertion of tautology */
    insert_clause(&f, &cb);
    print_cnf(&f); printf("\texpected [3:(bC)]\n");

    /* test variable counting with skipped variables */
    insert_clause(&f, &cc);
    print_cnf(&f); printf("\texpected [9:(bC)(hCi)]\n");

    /* test insertion of duplicate but permuted clause */
    insert_clause(&f, &cd);
    print_cnf(&f); printf("\texpected [9:(bC)(hCi)]\n");

    /* test insertion of weaker clause */
    insert_clause(&f, &ce);
    print_cnf(&f); printf("\texpected [9:(bC)(hCi)]\n");

    /* test insertion of stronger clause */
    insert_clause(&f, &cf);
    print_cnf(&f); printf("\texpected [9:(C)]\n");

    destroy_cnf(&f);
    destroy_clause(&ca);
    destroy_clause(&cb);
    destroy_clause(&cc);
    destroy_clause(&cd);
    destroy_clause(&ce);
    destroy_clause(&cf);
    printf("\n");
}
