#ifndef EXPR_H
#define EXPR_H 

#include <stdlib.h>

//#define GARBAGE_COLLECTOR 1

typedef char bool;
#define true 1
#define false 0

/* a. variables */
// positive chars.  negation encoded by additive inverse;
typedef char Var;
#define neg(v) (-(v))
#define abs(v) ((v)>0 ? (v) : -(v))

/* b. clauses */
typedef struct {
    int len;
    int cap;
    Var* vars;  
    bool taut;
} Clause;

void construct_clause(Clause* cptr);

void insert_var(Clause* cptr, Var var);

void destroy_clause(Clause* cptr);

void print_clause(Clause* cptr);

bool implies(Clause* lhsptr, Clause* rhsptr);

/* c. formulae in conjunctive normal form */
typedef struct {
    int nb_vars; // bound on number of variables involved; assumes inserted clauses do not change.
    int len;
    int cap;
    Clause** cptrs;
} CNF;

void construct_cnf(CNF* cnfptr);

void insert_clause(CNF* cnfptr, Clause* cptr);

void destroy_cnf(CNF* cnfptr);

void print_cnf(CNF* cnfptr);


#endif//EXPR_H
