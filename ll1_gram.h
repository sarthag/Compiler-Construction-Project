// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------

#ifndef LL1_GRAM_H
#define LL1_GRAM_H
#include "ll1_gramDef.h"


lhs G[NUM_OF_RULES];
int get_id(char *str, int t);
bool isTerm(char* str);
void generateGrammar();
void populate_grammar();
void loadFirstFollow();
void findFirst(lhs target);
void findFollow(lhs start, rhs *target, rhs *temp, int rule);
void computeFirstandFollow();
void print_ff(int r);

#endif