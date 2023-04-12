// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------

#ifndef ASTADTDEF_H
#define ASTADTDEF_H

#include "parser.h"

// typedef struct regNode{
//     struct astNode *leftChild;
// }regNode;
// typedef struct listElm{
//     struct listElm *prevElm;
// }listElm;
// typedef struct listHead{
//     struct astNode *leftChild;
//     struct listElm *firstNode; //points to the first element of the list 
//     struct listElm *lastNode; //points to the last element of the list 
// } listHead;


typedef struct astNode{
    union {
        non_terminal nt;
        token t;
    }name;

    node_type nodeType;
    int rule_no;
    struct astNode *parent;
    struct astNode *rightSibling; 
    struct astNode * leftChild;
    tree_node *pt;
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

int astNodes; 


#endif 