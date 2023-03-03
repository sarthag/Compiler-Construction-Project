#ifndef LL1_GRAMDEF_H
#define LL1_GRAMDEF_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "adt.h"

#define MAX_LINE_LENGTH 200
#define NUM_OF_RULES 138
#define NUM_OF_TERMINALS 59
#define NUM_OF_NONTERMINALS 73

bool sync_set[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
int First[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
int Follow[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
typedef struct rhs_struct{
    int rhs_id;
    bool isTerminal;
    struct rhs_struct* nextRHS;
    struct rhs_struct* prevRHS;
} rhs;

typedef struct lhs_struct{
    int lhs_id;
    rhs* firstRHS;
    rhs* lastRHS; 
} lhs; 


#endif