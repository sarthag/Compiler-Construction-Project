#ifndef ICGENERATIONDEF_H 
#define ICGENERATIONDEF_H 

#include "symbolTable.h"

typedef enum ICGlabels{
    INT_ADD, INT_SUB, INT_MUL, INT_DIV
}icgLabels;

/*
To access the labels
1. check if terminal or non-terminal 
2. if terminal, access lexeme form token 
3. if non-terminal, access the NT name
*/

typedef struct icgTuple{
    icgLabels label;
    symbolRecord* lhs; 
    symbolRecord* op1; 
    symbolRecord* op2; 
    //token immediateVal;
    char* jump; // need to figure out later if this should remain a char
}icgTuple;


#endif