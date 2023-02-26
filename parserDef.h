#include <stdio.h>
#include <stdbool.h>
//array of LHS grammar G 

#define NUM_OF_RULES 7
#define NUM_OF_TERMINALS 3
#define NUM_OF_NONTERMINALS 4
#define PT_COLS 4

typedef struct rhs_struct{
    int rhs_id;
    bool isTerminal;
    struct rhs_struct* nextRHS;
} rhs;

typedef struct {
    int lhs_id;
    rhs* firstRHS;
} lhs; 





lhs G[NUM_OF_RULES];
int parse_table[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS+1];
//array of follow and first

//array of parsing table

/*
typedef enum {
    start, module, otherModules, moduleDef, epsilon
} non_term;

typedef enum {
    ID,NUM,COLON
} term;

typedef union {
    term t;
    non_term nt;
}symb;
*/