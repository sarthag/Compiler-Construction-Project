// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------


#ifndef LEXER_H
#define LEXER_H
//Contains function prototype declarations of functions in lexer.c
#include "lexerDef.h"

FILE * readFile(char *filename);
FILE *getStream(FILE *code);
char getNextChar(FILE *code);

token* addTokenToList();
void resetLexeme();
void retract(int n);
char *getLexeme(); 

void getNextToken(FILE* code);
void removeComments(char *filename);
token_key tokenizeIDorKeyword(char* lexeme, ktElement keywordTable[]);
void populate_keyword_table(); 


#endif