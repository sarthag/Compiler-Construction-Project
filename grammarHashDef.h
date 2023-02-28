#ifndef NTHASHTABLEDEF_H
#define NTHASHTABLEDEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define PRIME 31 
#define KTSIZE 199
#define MOD 1e9+7
#define NTSIZE 30


#endif
typedef enum {
    START
}nt_key;

typedef enum{
    MINUS, NE, BO, BC, MUL, COMMENTMARK, COMMA, RANGEOP, DIV, COLON, ASSIGNOP, SEMICOL, SQBO, SQBC, PLUS, LT, DEF, DRIVERDEF, LE, EQ, GT, GE, ENDDEF, DRIVERENDDEF, NUM, RNUM, ID, AND, ARRAY, BOOLEAN, BREAK, CASE, DECLARE, DEFAULT, DRIVER, END, FOR, GET_VALUE, IN, INPUT, INTEGER, MODULE, OF, OR, PARAMETERS, PRINT, PROGRAM, REAL, RETURNS, START, SWITCH, TAKES, USE, WHILE, WITH, FALSE, TRUE, $,EPSILON
}token_key;

//node_type type;
    union {
        nt_key nt;
        token_key t;
    } element;