#ifndef SOLVER_H
#define SOLVER_H 

#include <stdlib.h>
#include "expr.h"

typedef struct {
    int nb_vars;
    int nb_assigned;
    Clause assignments; // really, a Varset
} Assignment;

// TODO: write:
bool satisfies(Assignment* full_assptr, CNF* cnfptr);
// TODO: write:
void solve(Assignment* assptr, CNF* cnfptr);

#endif//SOLVER_H
