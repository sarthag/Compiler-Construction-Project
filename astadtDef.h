#ifndef ASTADTDEF_H
#define ASTADTDEF_H

#include "parser.h"


typedef enum {
   LABEL
} labels;


typedef struct astNode{
    labels label; 
    int rule_no;
    int childast;
    int sibast;
    
    int isHead; //0- Child | 1-ListHead 
    int isListElm; //0- sibiling | 1-list Element 
    
    struct astNode *parent; 
    union{
        struct astNode *leftChild;
        struct listHead *head;
    }child;

    union{
        struct astNode *rightSibling; 
        struct astNode *nextList; 
    }nextElm;
    
    struct treenode *pt;
} astNode; 

typedef struct listHead{
    struct astNode *firstNode; //points to the first element of the list 
    struct astNode *lastNode; //points to the last element of the list 
} listHead;

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