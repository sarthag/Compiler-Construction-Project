// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------


#ifndef ASTDEF_H
#define ASTDEF_H

#include "astadt.h"   

astStack* syntaxStack;
ast* syntaxTree;


#define NUM_OF_RELEVANT 33

char* needed[NUM_OF_RELEVANT] = {"PLUS", "MINUS", "MUL", "DIV", "EPSILON", "ID", "INTEGER", "REAL", "BOOLEAN", "RANGEOP", "ASSIGNOP", "TRUE", "FALSE", "NUM", "RNUM", "DECLARE", "START", "END", "LT", "LE", "EQ", "NE", "GT", "GE", "AND", "OR", "ARRAY", "CASE", "FOR", "GET_VALUE", "PRINT", "WHILE", "SWITCH"};

int binRelevant[NUM_OF_TERMINALS];

#endif