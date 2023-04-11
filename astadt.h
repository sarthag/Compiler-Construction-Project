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
void countASTNodes(astNode *node);

#endif