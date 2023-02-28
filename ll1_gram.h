

#ifndef LL1_GRAM_H
#define LL1_GRAM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ll1_gramDef.h"

#define MAX_LINE_LENGTH 50
#define NUM_OF_RULES 7
#define NUM_OF_TERMINALS 4
#define NUM_OF_NONTERMINALS 4


lhs G[NUM_OF_RULES];
int get_id(char *str, int t);
bool isTerm(char* str);
void generateGrammar();


#endif