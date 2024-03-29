// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------


#ifndef LEXERDEF_H
#define LEXERDEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keywordTable.h"

#define BUFFERSIZE 1048575

typedef struct twinBuffer{
    char buffer1[BUFFERSIZE+1];
    char buffer2[BUFFERSIZE+1];
}twinBuffer;


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

//Linked List to Store Tokens
typedef struct tokenLL{
    token* start;
    token* end;
    int tokenCount;

}tokenLL;

//end of TOKEN LL


ktElement keyword_table[KTSIZE];

char *begin, *forward;
bool eof;
bool started;
int line_no;
int numChar;
int state;
int err;
tokenLL tokenList;
int lexemeCount;
#endif