#ifndef LL1_GRAM_H
#define LL1_GRAM_H

#include "parser.h"

#define MAX_LINE_LENGTH 50
int get_id(char *str, int t);
bool isTerm(char* str);
void generateGrammar();


#endif