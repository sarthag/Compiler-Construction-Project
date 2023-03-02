

#ifndef LL1_GRAM_H
#define LL1_GRAM_H
#include "ll1_gramDef.h"

#define MAX_LINE_LENGTH 200
#define NUM_OF_RULES 139
#define NUM_OF_TERMINALS 59
#define NUM_OF_NONTERMINALS 73


lhs G[NUM_OF_RULES];
int get_id(char *str, int t);
bool isTerm(char* str);
void generateGrammar();
void populate_grammar();

#endif