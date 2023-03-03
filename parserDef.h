#ifndef PARSERDEF_H
#define PARSERDEF_H

#include "ll1_gram.h"   /// Check this 
#include "computeFirstandFollow.h"
//array of LHS grammar G 

int parse_table[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
//array of follow and first
stack* parserStack;
parse_tree* parseTree;
token * L;

#endif