#ifndef PARSERDEF_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//array of LHS grammar G 

#define NUM_OF_RULES 7
#define NUM_OF_TERMINALS 4
#define NUM_OF_NONTERMINALS 4
#define PT_COLS 4

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


bool First[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
bool firstDone[NUM_OF_NONTERMINALS];


lhs G[NUM_OF_RULES];
int parse_table[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS+1];
//array of follow and first

typedef enum {
    
} nt_key;


nt_key nt_list[] = {};
#endif