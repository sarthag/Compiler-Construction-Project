// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------


#ifndef ADTDEF_H
#define ADTDEF_H 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grammarHash.h"


static char* nt_list[] = {
    "actualParaList", "anyTerm", "arithmeticExpr", "arithmeticOrBooleanExpr", "arrExpr", "arrFactor", "arrTerm", "arr_N4", "arr_N5", "assignmentStmt", "boolConstt", "caseStmt1", "caseStmt2", "conditionalStmt", "dataType", "declareStmt", "default1", "driverModule", "element_index_with_expressions", "expression", "factor", "idList1", "idList2", "id_num_rnum", "index_arr", "index_for_loop", "input_plist1", "input_plist2", "ioStmt", "iterativeStmt", "logicalOp", "module", "moduleDeclaration", "moduleDeclarations", "moduleDef", "moduleReuseStmt", "n1", "n2", "n3", "n4", "n5", "n6", "n7", "n8", "n9", "new_NT", "new_index", "new_index_for_loop", "op1", "op2", "optional", "otherModules", "output_plist1", "output_plist2", "p1", "program", "range_arrays", "range_for_loop", "relationalOp", "ret", "sign", "simpleStmt", "statement", "statements", "term", "type", "u", "value", "var_id_num", "var_print", "valueIDStmt", "valueARRStmt", "whichStmt"
};


static char* token_list[] = {
    "MINUS", "NE", "BO", "BC", "MUL", "COMMENTMARK", "COMMA", "RANGEOP", "DIV", "COLON", "ASSIGNOP", "SEMICOL", "SQBO", "SQBC", "PLUS", "LT", "DEF", "DRIVERDEF", "LE", "EQ", "GT", "GE", "ENDDEF", "DRIVERENDDEF", "NUM", "RNUM", "ID", "AND", "ARRAY", "BOOLEAN", "BREAK", "CASE", "DECLARE", "DEFAULT", "DRIVER", "END", "FOR", "GET_VALUE", "IN", "INPUT", "INTEGER", "MODULE", "OF", "OR", "PARAMETERS", "PRINT", "PROGRAM", "REAL", "RETURNS", "START", "SWITCH", "TAKES", "USE", "WHILE", "WITH", "FALSE", "TRUE", "$", "EPSILON"
};


typedef struct nonTerminal{
    nt_key nid;
} non_terminal; 


typedef enum {
    NON_TERMINAL,
    TERMINAL
} node_type;


typedef struct stack_node {
    node_type type;
    union {
        non_terminal nt;
        token t;
    } element;
    struct stack_node *next;
    struct tree_node *treeLocation;
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
    int rule;
    int is_visited;
} tree_node;

typedef struct parse_tree {
    tree_node *root;
} parse_tree;

#endif 