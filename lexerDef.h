#include <stdio.h>
#include <stdbool.h>
//array of LHS grammar G 

#define BUFFERSIZE 65535

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
typedef struct rhs_struct{
    int rhs_id;
    bool isTerminal;
    struct rhs_struct *nextRHS;
} rhs;

typedef struct {
    int lhs_id;
    rhs* firstRHS;
} lhs; 





typedef struct token{
    token_key tid; 
    union{
        char* lexeme; 
        int num;
        double rnum;
    };
    int line_no; 
    struct token *next; // Makes the struct a linked list
} token;

ktElement keyword_table[KTSIZE];
