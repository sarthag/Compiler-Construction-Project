#include <stdio.h>
#include <stdbool.h>
//array of LHS grammar G 

#define NUM_OF_RULES 7
#define NUM_OF_TERMINALS 3
#define NUM_OF_NONTERMINALS 5


typedef enum {
    S, A, B, C, epsilon
} non_term;

typedef enum {
    a,b,c
} term;

typedef union {
    term t;
    non_term nt;
}symb;


typedef struct lhs{
    non_term lhs_v;
    struct rhs *firstRHS;
} lhs; 

typedef struct rhs{
    symb rhs_v;
    bool isTerm;
    struct rhs *nextRHS;
} rhs;


lhs G[NUM_OF_RULES];

//array of follow and first

//array of parsing table