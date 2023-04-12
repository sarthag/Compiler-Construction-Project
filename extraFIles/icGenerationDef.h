#ifndef ICGENERATIONDEF_H 
#define ICGENERATIONDEF_H 

#include "symbolTable.h"
#define MAXLINES 5000

typedef enum ICGlabels{
    INT_ADD, INT_SUB, INT_MUL, INT_DIV, REAL_ADD, REAL_SUB, REAL_MUL, REAL_DIV, INT_TO_REAL, BOOL_AND, BOOL_OR, ROP_INT_LT, ROP_INT_LE, ROP_INT_EQ, ROP_INT_NE, ROP_INT_GT, ROP_INT_GE, ROP_REAL_LT, ROP_REAL_LE, ROP_REAL_EQ, ROP_REAL_NE, ROP_REAL_GT, ROP_REAL_GE,ASSIGN_INT,ASSIGN_REAL,ASSIGN_BOOL
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