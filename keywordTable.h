// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------



#ifndef KEYWORDTABLE_H
#define KEYWORDTABLE_H

#include "keywordTableDef.h"

int hash(const char *lexeme);

void initializeKeywordTable(ktElement keywordTable[], int size);
void insert(const char *lexeme, token_key token, ktElement keywordTable[]);
token_key getTokenFromKT(char *lexeme, ktElement keywordTable[]);
void printKeywordTable(ktElement keywordTable[], int ktSize);

#endif