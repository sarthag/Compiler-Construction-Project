// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------

#ifndef ADT_H
#define ADT_H 

#include "adtDef.h"

//Stack
void initStack(stack* s);
stack_node* create_stack_node(node_type type, void* element, tree_node* treeLocation);
void push(stack* s, node_type type, int id, tree_node* treeLocation);
stack_node* pop(stack* s);
void printStack(stack* s);


//Tree
parse_tree *create_parse_tree();
tree_node *create_node(node_type type, int id);
void insert_child(tree_node *parent, tree_node *child);
void set_sibling(tree_node *node, tree_node *sibling);
void set_parent(tree_node *node, tree_node *parent);
void delete_node(tree_node *node);
void inorder_traversal(tree_node *node, FILE * fp);



#endif