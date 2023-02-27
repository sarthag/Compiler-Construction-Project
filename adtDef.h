#ifndef ADTDEF_H
#define ADTDEF_H 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lexer.h"

typedef enum {
} nt_key;

nt_key nt_list[] = {};


typedef struct nonTerminal{
    nt_key nid;
} non_terminal; 


typedef enum {
    TERMINAL,
    NON_TERMINAL
} node_type;


struct Node {
    int id; 
    int line_no; 
    node_type nodeType; 
    struct Node* next;
};

struct Stack {
    struct Node* top;
};

















































//TREE
// need is visited and union of both
// use node type

typedef struct tree_node {
    node_type type;
    int id; 
    bool isVisited;
    struct tree_node *parent;
    struct tree_node *left_child;
    struct tree_node *right_sibling;
} TreeNode;


typedef struct parse_tree {
    TreeNode *root;
    int size;
} ParseTree;

#endif 