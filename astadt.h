#ifndef ASTADT_H
#define ASTADT_H 

#include "astadtDef.h"

void initASTStack(astStack* s);
astStackNode* createastStackNode(astNode *treeloc);
void pushast(astStack* s, astNode *treeloc);
astStackNode* popast(astStack* s);


ast *createSyntaxTree();
astNode* createASTNode(node_type nodeType,int rule_no, tree_node* pTNode);
void insertASTchild(astNode *parent, astNode* child, int parentType);
void setASTSibling(astNode *node, astNode *sibling);
void setASTparent(astNode *node, astNode *parent) ;

#endif