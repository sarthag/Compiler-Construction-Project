

#ifndef LL1_GRAM_H
#define LL1_GRAM_H
#include "ll1_gramDef.h"


lhs G[NUM_OF_RULES];
int get_id(char *str, int t);
bool isTerm(char* str);
void generateGrammar();
void populate_grammar();

#endif