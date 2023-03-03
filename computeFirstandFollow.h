#ifndef COMPUTEFIRSTANDFOLLOW_H
#define COMPUTEFIRSTANDFOLLOW_H

#include "ll1_gram.h"
#include "keywordTable.h"

// bool First[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
// bool firstDone[NUM_OF_NONTERMINALS];
// bool Follow[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS] = {0};


int f1[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
bool f1Done[NUM_OF_NONTERMINALS];
int f2[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
bool f2Done[NUM_OF_NONTERMINALS];

void findf1(lhs target);
void findf2(lhs start, rhs *target, rhs *temp);
void computef1andf2();
void syncronization_set();

#endif