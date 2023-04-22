// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------


#ifndef AST_H
#define AST_H 

#include "astDef.h"
void createRelevant();
void topDownPass(astNode* parent, tree_node *parseNode, astStack* syntaxStack);
void printASTstack(astStack * syntaxStack);
astNode* findAction(astNode * current, astNode * prev, astNode * lastTerminal);
astNode* callfindAction(astNode* ASTroot, astStack* syntaxStack);
astStack* initAST();


#endif