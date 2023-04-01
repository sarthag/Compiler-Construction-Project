#ifndef ASTADTDEF_H
#define ASTADTDEF_H

#include "parser.h"


typedef enum {
   
} labels;


typedef struct astNode{
    labels label; 
    int rule_no;
    int childast;
    int sibast;

    struct astNode *parent; 
    
    union{
    struct astNode *leftChild;
    struct tree_node *parseTreeChild;
    }child;

    union{
    struct astNode *rightSibling;
    struct tree_node *parseTreeSib;
    }sibling;  
} astNode; 


typedef struct ast{
    struct astNode* root;
} ast;


// Stack

typedef struct astStackNode {
    struct astNode *treeloc;
    struct astStackNode *next;
} astStackNode;


typedef struct astStack {
    int size;
    astStackNode *top;
} astStack;


#endif 