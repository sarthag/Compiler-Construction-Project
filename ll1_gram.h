

#ifndef LL1_GRAM_H
#define LL1_GRAM_H
#include "ll1_gramDef.h"

#define MAX_LINE_LENGTH 50
#define NUM_OF_RULES 131
#define NUM_OF_TERMINALS 61
#define NUM_OF_NONTERMINALS 76


lhs G[NUM_OF_RULES];
int get_id(char *str, int t);
bool isTerm(char* str);
void generateGrammar();
void populate_grammar();

#endif