#ifndef GRAMMARHASH_H
#define GRAMMARHASH_H

#include "grammarHashDef.h"

int hashGrammar(const char *element);

//for Non Terminal Hashing
void initializeNTTable(ntElement ntTable[], int size);
void insertNonTerminal(const char *ntText, nt_key nonTerminal, ntElement ntTable[]);
nt_key getTokenFromNTTable(char *ntText, ntElement ntTable[]);
void printNTTable(ntElement ntTable[], int ntSize);

//for Terminal hashing
void initializeTTable(tElement tTable[], int size);
void insertTerminal(const char *tText, token_key terminal, tElement tTable[]);
token_key getTokenFromTTable(char *tText, tElement tTable[]);
void printTTable(tElement tTable[], int tSize);




#endif