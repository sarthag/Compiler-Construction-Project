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
// #include "adtDef.h"
//array of LHS grammar G 
//array of follow and first
astStack* syntaxStack;
ast* syntaxTree;


#define NUM_OF_RELAVENT 2

char* relavent[NUM_OF_RELAVENT] = {"PLUS", "MINUS"};
int labels[NUM_OF_TERMINALS] = {0};

#endif