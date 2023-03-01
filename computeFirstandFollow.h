#ifndef COMPUTEFIRSTANDFOLLOW_H
#define COMPUTEFIRSTANDFOLLOW_H

#include "ll1_gram.h"
#include "keywordTable.h"

// bool First[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
// bool firstDone[NUM_OF_NONTERMINALS];
// bool Follow[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS] = {0};


int First[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
bool firstDone[NUM_OF_NONTERMINALS];
int Follow[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
bool sync_set[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];

void findFirst(lhs target);
void findFollow(lhs start, rhs *target, rhs *temp);
void computeFirstandFollow();
void syncronization_set();

#endif