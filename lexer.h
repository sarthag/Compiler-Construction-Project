//Contains function prototype declarations of functions in lexer.c

#include "lexerDef.h";

FILE *getStream(FILE *fp);
void getNextToken();
void removeComments(char *testcaseFile, char *cleanFile);

FILE * readFile();