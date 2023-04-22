// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------

#ifndef KEYWORDTABLEDEF_H
#define KEYWORDTABLEDEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define PRIME 31 
#define KTSIZE 97
#define MOD 1e9+7
#define LEXEMESIZE 30

typedef enum {
    MINUS, NE, BO, BC, MUL, COMMENTMARK, COMMA, RANGEOP, DIV, COLON, ASSIGNOP, SEMICOL, SQBO, SQBC, PLUS, LT, DEF, DRIVERDEF, LE, EQ, GT, GE, ENDDEF, DRIVERENDDEF, NUM, RNUM, ID, AND, ARRAY, BOOLEAN, BREAK, CASE, DECLARE, DEFAULT, DRIVER, END, FOR, GET_VALUE, IN, INPUT, INTEGER, MODULE, OF, OR, PARAMETERS, PRINT, PROGRAM, REAL, RETURNS, START, SWITCH, TAKES, USE, WHILE, WITH, FALSE, TRUE, $, EPSILON
} token_key;


typedef struct ktElement{
    char lexeme[LEXEMESIZE];
    token_key  token;
    bool occupied;
}ktElement;

// ktElement keywordTable[KTSIZE];

#endif