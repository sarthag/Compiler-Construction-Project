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
    struct astNode *leftChild;
    struct astNode *rightSibling; 
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