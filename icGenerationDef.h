#ifndef ICGENERATIONDEF_H 
#define ICGENERATIONDEF_H 

#include "symbolTable.h"
#define MAXLINES 5000

typedef enum ICGlabels{
    INT_ADD, INT_SUB, INT_MUL, INT_DIV, REAL_ADD, REAL_SUB, REAL_MUL, REAL_DIV, INT_TO_REAL
}icgLabels;

/*
To access the labels
1. check if terminal or non-terminal 
2. if terminal, access lexeme form token 
3. if non-terminal, access the NT name
*/

typedef struct icgLine{
    icgLabels label;
    symbolRecord* lhs; 
    symbolRecord* op1; 
    symbolRecord* op2; 
    //token immediateVal;
    char* jump; // need to figure out later if this should remain a char
}icgLine;

icgLine intermediateCode[MAXLINES];
int icgLineNo;

#endif