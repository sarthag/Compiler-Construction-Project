#include "keywordTableDef.h"

int hash(const char *lexeme);

void initializeKeywordTable(ktElement keywordTable[], int size);
void insert(const char *lexeme, token_key token, ktElement keywordTable[]);
token_key getTokenFromKT(char *lexeme, ktElement keywordTable[]);
bool isPresent(ktElement keywordTable[], char *lexeme);
void printKeywordTable(ktElement keywordTable[], int ktSize);