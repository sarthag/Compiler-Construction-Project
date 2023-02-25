#include "keywordTableDef.h";

int hash(char *lexeme, int size);

void initializeKeywordTable(ktElement keywordTable[], int size);
int insert(char *lexeme, int token, ktElement keywordTable[]);
bool isPresent(ktElement keywordTable[], char *lexeme ,int lexemeSize);
char* get(char *lexeme, ktElement keywordTable[]);