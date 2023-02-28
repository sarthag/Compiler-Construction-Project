#ifndef GRAMMARHASHDEF_H
#define GRAMMARHASHDEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define PRIME 31
#define NTSIZE 349
#define TSIZE 349
#define MOD 1e9+7
#define NTTEXTSIZE 30
#define TTEXTSIZE 30
//for non terminal hash table
typedef enum {
    STARTCODE
}nt_key;

typedef struct ntElement{
    char ntText[NTTEXTSIZE];
    nt_key  nonTerminal;
    bool occupied;
}ntElement;


// for terminal hash table
typedef enum{
    MINUS, NE, BO, BC, MUL, COMMENTMARK, COMMA, RANGEOP, DIV, COLON, ASSIGNOP, SEMICOL, SQBO, SQBC, PLUS, LT, DEF, DRIVERDEF, LE, EQ, GT, GE, ENDDEF, DRIVERENDDEF, NUM, RNUM, ID, AND, ARRAY, BOOLEAN, BREAK, CASE, DECLARE, DEFAULT, DRIVER, END, FOR, GET_VALUE, IN, INPUT, INTEGER, MODULE, OF, OR, PARAMETERS, PRINT, PROGRAM, REAL, RETURNS, START, SWITCH, TAKES, USE, WHILE, WITH, FALSE, TRUE, $,EPSILON
}token_key;

typedef struct tElement{
    char tText[TTEXTSIZE];
    token_key  terminal;
    bool occupied;
}tElement;

ntElement nonTerminalHash[NTSIZE];
tElement terminalHash[TSIZE];

#endif