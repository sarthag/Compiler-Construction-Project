//Contains function prototype declarations of functions in lexer.c
#include "lexerDef.h";

FILE * readFile(char *filename);
FILE *getStream(FILE *code);
char getNextChar(FILE *code);

token* addTokenToList();
void resetLexeme();
void retract(int n);
char *getLexeme(); 

token getNextToken(FILE* code);
void removeComments(char *testcaseFile, char *cleanFile);

void populate_keyword_table(); 
