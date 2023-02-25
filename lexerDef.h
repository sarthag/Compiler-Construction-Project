#ifndef LEXERDEF_H
#define LEXERDEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keywordTable.h"

#define BUFFERSIZE 1023

typedef struct twinBuffer{
    char buffer1[BUFFERSIZE+1];
    char buffer2[BUFFERSIZE+1];
}twinBuffer;

//Linked List to Store Tokens
typedef struct tokenLL{
    token* start;
    token* end;
    int tokenCount;

}tokenLL;


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
#endif