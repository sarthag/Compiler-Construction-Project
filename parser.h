#ifndef PARSER_H
#define PARSER_H 

#include "parserDef.h"



//read fake txt file
//first symbol to lhs and rest to rhs
//populate the array 

void synchronization_set();
void populate_parse_table();
void InitializeParser();
void parser_retract(non_terminal nonterm, token* current);
void printParseTree(tree_node *node, char* parseTreeFile);
void parse_code();

#endif