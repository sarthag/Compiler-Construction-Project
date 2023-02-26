#ifndef KEYWORDTABLE_H
#define KEYWORDTABLE_H

#include "keywordTableDef.h"

int hash(const char *lexeme);

void initializeKeywordTable(ktElement keywordTable[], int size);
void insert(const char *lexeme, token_key token, ktElement keywordTable[]);
token_key getTokenFromKT(char *lexeme, ktElement keywordTable[]);
void printKeywordTable(ktElement keywordTable[], int ktSize);

#endif