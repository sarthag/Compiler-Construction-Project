//Contains function prototype declarations of functions in lexer.c

#include "lexerDef.h";

FILE * readFile();
FILE *getStream(FILE *fp);
char getNextChar(FILE *fp);
token getNextToken();
void removeComments(char *testcaseFile, char *cleanFile);


void retract(int num_char); 
void populate_keyword_table(); 
token_key getTokenFromKT(char* lexeme);
