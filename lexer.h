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