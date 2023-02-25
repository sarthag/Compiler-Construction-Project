#ifndef LEXERDEF_H
#define LEXERDEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keywordTable.h"

#define BUFFERSIZE 65535

typedef struct twinBuffer{
    char buffer1[BUFFERSIZE+1];
    char buffer2[BUFFERSIZE+1];
}twinBuffer;


typedef enum {
    MINUS, NE, BO, BC, MUL, COMMENTMARK, COMMA, RANGEOP, DIV, COLON, ASSIGNOP, SEMICOL, SQBO, SQBC, PLUS, LT, DEF, DRIVERDEF, LE, EQ, GT, GE, ENDDEF, DRIVERENDDEF, NUM, RNUM, ID, AND, ARRAY, BOOLEAN, BREAK, CASE, DECLARE, DEFAULT, DRIVER, END, FOR, GET_VALUE, IN, INPUT, INTEGER, MODULE, OF, OR, PARAMETERS, PRINT, PROGRAM, REAL, RETURNS, START, SWITCH, TAKES, USE, WHILE, WITH, FALSE, TRUE
} token_key;


token_key token_list[] = {
    MINUS, NE, BO, BC, MUL, COMMENTMARK, COMMA, RANGEOP, DIV, COLON, ASSIGNOP, SEMICOL, SQBO, SQBC, PLUS, LT, DEF, DRIVERDEF, LE, EQ, GT, GE, ENDDEF, DRIVERENDDEF, NUM, RNUM, ID, AND, ARRAY, BOOLEAN, BREAK, CASE, DECLARE, DEFAULT, DRIVER, END, FOR, GET_VALUE, IN, INPUT, INTEGER, MODULE, OF, OR, PARAMETERS, PRINT, PROGRAM, REAL, RETURNS, START, SWITCH, TAKES, USE, WHILE, WITH, FALSE, TRUE
};


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

#endif