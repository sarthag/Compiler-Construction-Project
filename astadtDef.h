#ifndef ASTADTDEF_H
#define ASTADTDEF_H

#include "parser.h"

typedef struct regNode{
    struct astNode *leftChild;
}regNode;
typedef struct listElm{
    struct listElm *prevElm;
}listElm;
typedef struct listHead{
    struct astNode *leftChild;
    struct listElm *firstNode; //points to the first element of the list 
    struct listElm *lastNode; //points to the last element of the list 
} listHead;


typedef struct astNode{
    //labels label;
    union {
        non_terminal nt;
        token t;
    }name;

    node_type nodeType;

    int rule_no;
    
    int typeId;

    struct astNode *parent;
    struct astNode *rightSibling; 
    union{
        regNode *reg;
        listElm *listNode;
        listHead *head;
    } type;
    
    tree_node *pt;
} astNode; 



typedef struct ast{
    struct astNode* root;
} ast;


// Stack

typedef struct astStackNode {
    struct tree_node *treeloc;
    struct astStackNode *next;
} astStackNode;


typedef struct astStack {
    int size;
    astStackNode *top;
} astStack;


#endif 