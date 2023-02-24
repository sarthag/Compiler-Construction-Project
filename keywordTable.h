#include "keywordTableDef.h";

int hash(char *lexeme, int size);

void initializeKeywordTable(ktElement keywordTable[], int size);
int insert(char *lexeme, int lexemeSize, int token, ktElement keywordTable[]);
bool isPresent(ktElement keywordTable[],char *lexeme ,int lexemeSize);
char* get(char *lexeme, int lexemeSize, ktElement keywordTable[]);