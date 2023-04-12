// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------

#ifndef ASTADT_H
#define ASTADT_H 

#include "astadtDef.h"

void initASTStack(astStack* s);
astStackNode* createastStackNode(astNode *treeloc);
void pushast(astStack* s, astNode *treeloc);
astStackNode* popast(astStack* s);


ast *createSyntaxTree();
astNode* createASTNode(node_type nodeType,int rule_no, tree_node* pTNode);
void deleteASTnode(astNode * node);
void ast_traversal(astNode *node); 
void printASTnode(astNode*node);
void countASTNodes(astNode *node);

#endif