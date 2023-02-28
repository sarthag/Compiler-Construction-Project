#ifndef PARSERDEF_H
#define PARSERDEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "adt.h"   /// Check this 
//array of LHS grammar G 

#define PT_COLS 4



int parse_table[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS+1];
//array of follow and first
stack* parserStack;
parse_tree* parseTree;
token * L;

#endif