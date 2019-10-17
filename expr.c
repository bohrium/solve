#include <stdio.h>
#include "expr.h"

void construct_clause(Clause* cptr)
{
    cptr->cap = 4;
    cptr->vars = malloc(cptr->cap * sizeof(Var));
    cptr->len = 0;
    cptr->taut = false;
}

void insert_var(Clause* cptr, Var var)
{
    if (cptr->taut) {
        return;
    }
    for (int v=0; v!=cptr->len; ++v) {
        if (cptr->vars[v] == var) { // A. do nothing
            return;
        } else if (cptr->vars[v] == neg(var)) { // B. become tautology
            destroy_clause(cptr);
            cptr->taut = true;
            return;
        }
    } 
    // C. insert var, expanding as necessary
    if (cptr->len == cptr->cap) {
        cptr->cap = (3*cptr->cap)/2 + 1;
        Var* new_vars = malloc(cptr->cap * sizeof(Var));
        for (int v=0; v!=cptr->len; ++v) {
            new_vars[v] = cptr->vars[v];
        }
        free(cptr->vars);
        cptr->vars = new_vars;
    }
    cptr->vars[cptr->len] = var; 
    cptr->len += 1;
}

void destroy_clause(Clause* cptr)
{
    cptr->cap = 0;
    free(cptr->vars);
    cptr->vars = NULL;
    cptr->len = 0;
}

void print_clause(Clause* cptr)
{
    if (cptr->taut) {
        printf("T");
    } else {
        printf("(");
        for (int v=0; v!=cptr->len; ++v) {
            printf("%c", (0 < cptr->vars[v]) ? 
                            (+cptr->vars[v])-1 + 'A' :
                            (-cptr->vars[v])-1 + 'a'
            );
        }
        printf(")");
    }
}

bool implies(Clause* lhsptr, Clause* rhsptr)
{
    if (rhsptr->taut) {
        return true;
    } else if (lhsptr->taut) {
        return false;
    }
    for (int vl=0; vl!=lhsptr->len; ++vl) {
        bool match = false; 
        for (int vr=0; vr!=rhsptr->len; ++vr) {
            if (lhsptr->vars[vl] == rhsptr->vars[vr]) {
                match = true;
                break; 
            }
        }
        if (!match) {
            return false;
        }
    }
    return true;
}


void construct_cnf(CNF* cnfptr)
{
    cnfptr->cap = 4;
    cnfptr->cptrs = malloc(cnfptr->cap * sizeof(Clause*));
    cnfptr->len = 0;
    cnfptr->nb_vars = 0;
}

void insert_clause(CNF* cnfptr, Clause* cptr)
{
    for (int c=0; c!=cnfptr->len; ++c) {
        if (implies(cnfptr->cptrs[c], cptr)) {
            return;
        } else if (implies(cptr, cnfptr->cptrs[c])) {
            int write_index = 0;
            for (int cc=0; cc!=cnfptr->len; ++cc) {
                // throughout this loop, (write_index<=cc) is maintained.
                if (!implies(cptr, cnfptr->cptrs[cc])) {
                    cnfptr->cptrs[write_index] = cnfptr->cptrs[cc]; 
                    write_index += 1;
                }
            }
            cnfptr->cptrs[write_index] = cptr;
            cnfptr->len = write_index+1;
            return;
        }
    }

    /* a. expand if needed */
    if (cnfptr->len == cnfptr->cap) {
        cnfptr->cap = (3*cnfptr->cap)/2 + 1;
        Clause** new_cptrs = malloc(cnfptr->cap * sizeof(Clause*));
        for (int c=0; c!=cnfptr->len; ++c) {
            new_cptrs[c] = cnfptr->cptrs[c];
        }
        free(cnfptr->cptrs);
        cnfptr->cptrs = new_cptrs;
    }

    /* b. insert  */
    cnfptr->cptrs[cnfptr->len] = cptr; 
    cnfptr->len += 1;

    /* c. update nb_vars */
    for (int v=0; v!=cptr->len; ++v)
    {
        if (cnfptr->nb_vars < abs(cptr->vars[v])) {
            cnfptr->nb_vars = abs(cptr->vars[v]);
        }
    }
}

void destroy_cnf(CNF* cnfptr)
{
    cnfptr->cap = 0;
    free(cnfptr->cptrs);
    cnfptr->cptrs = NULL;
    cnfptr->len = 0;
}

void print_cnf(CNF* cnfptr)
{
    printf("[%d:", cnfptr->nb_vars);
    for (int c=0; c!=cnfptr->len; ++c) {
        print_clause(cnfptr->cptrs[c]);
    }
    printf("]");
}
