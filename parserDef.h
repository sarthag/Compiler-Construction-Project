#ifndef PARSERDEF_H
#define PARSERDEF_H

#include "adt.h"   /// Check this 
#include "computeFirstandFollow.h"
//array of LHS grammar G 

#define PT_COLS 4



int parse_table[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS+1];
bool sync_set[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
//array of follow and first
stack* parserStack;
parse_tree* parseTree;
token * L;

#endif