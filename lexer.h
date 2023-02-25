//Contains function prototype declarations of functions in lexer.c

#include "lexerDef.h";

FILE * readFile();
FILE* getFirstStream(FILE *code);
FILE *getStream(FILE *fp);
void getNextToken();
void removeComments(char *testcaseFile, char *cleanFile);


void retract(int num_char); 
void populate_keyword_table(); 
token_key search_keyword_table(char* lexeme);
