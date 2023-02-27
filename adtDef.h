#ifndef ADTDEF_H
#define ADTDEF_H 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lexer.h"

typedef enum {
    first
} nt_key;

char* nt_list[] = {
    "first"
};


char* token_list[] = {
    "MINUS", "NE", "BO", "BC", "MUL", "COMMENTMARK", "COMMA", "RANGEOP", "DIV", "COLON", "ASSIGNOP", "SEMICOL", "SQBO", "SQBC", "PLUS", "LT", "DEF", "DRIVERDEF", "LE", "EQ", "GT", "GE", "ENDDEF", "DRIVERENDDEF", "NUM", "RNUM", "ID", "AND", "ARRAY", "BOOLEAN", "BREAK", "CASE", "DECLARE", "DEFAULT", "DRIVER", "END", "FOR", "GET_VALUE", "IN", "INPUT", "INTEGER", "MODULE", "OF", "OR", "PARAMETERS", "PRINT", "PROGRAM", "REAL", "RETURNS", "START", "SWITCH", "TAKES", "USE", "WHILE", "WITH", "FALSE", "TRUE"
};

typedef struct nonTerminal{
    nt_key nid;
} non_terminal; 


typedef enum {
    TERMINAL,
    NON_TERMINAL
} node_type;


typedef struct stack_node {
    node_type type;
    union {
        non_terminal nt;
        token t;
    } element;
    struct stack_node *next;
} stack_node;


typedef struct Stack {
    int size;
    stack_node *top;
} stack;



//TREE
// need is visited and union of both
// use node type
typedef struct tree_node {
    union {
        non_terminal nt;
        token t;
    } element;
    node_type type;
    struct tree_node *parent;
    struct tree_node *left_child;
    struct tree_node *right_sibling;
    int is_visited;
} tree_node;

typedef struct parse_tree {
    tree_node *root;
} parse_tree;

#endif 