#ifndef ASTADT_H
#define ASTADT_H 

#include "astadtDef.h"

void initASTStack(astStack* s);
astStackNode* createastStackNode(tree_node *treeloc);
void pushast(astStack* s, tree_node *treeloc);
void popast(astStack* s);

ast *createSyntaxTree();
astNode* createASTNode(labels label, int rule_no);
void insertASTchild(astNode *parent, astNode* child);
void setASTSibling(astNode *node, astNode *sibling);
void setASTparent(astNode *node, astNode *parent) ;

#endif