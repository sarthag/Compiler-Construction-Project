// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------



#ifndef GRAMMARHASHDEF_H
#define GRAMMARHASHDEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lexer.h"

#define PRIME 31
#define NTSIZE 349
#define TSIZE 349
#define MOD 1e9+7
#define NTTEXTSIZE 30
#define TTEXTSIZE 30

//for non terminal hash table
typedef enum {
    actualParaList, anyTerm, arithmeticExpr, arithmeticOrBooleanExpr, arrExpr, arrFactor, arrTerm, arr_N4, arr_N5, assignmentStmt, boolConstt, caseStmt1, caseStmt2, conditionalStmt, dataType, declareStmt, default1, driverModule, element_index_with_expressions, expression, factor, idList1, idList2, id_num_rnum, index_arr, index_for_loop, input_plist1, input_plist2, ioStmt, iterativeStmt, logicalOp, module, moduleDeclaration, moduleDeclarations, moduleDef, moduleReuseStmt, n1, n2, n3, n4, n5, n6, n7 ,new_NT, new_index, new_index_for_loop, op1, op2, optional, otherModules, output_plist1, output_plist2, p1, program, range_arrays, range_for_loop, relationalOp, ret, sign, sign_for_loop, simpleStmt, statement, statements, term, type, u, unary_op, value, var_id_num, var_print, valueIDStmt, valueARRStmt, whichStmt
}nt_key;

typedef struct ntElement{
    char ntText[NTTEXTSIZE];
    nt_key  nonTerminal;
    bool occupied;
}ntElement;


// for terminal hash table
// typedef enum{
//     MINUS, NE, BO, BC, MUL, COMMENTMARK, COMMA, RANGEOP, DIV, COLON, ASSIGNOP, SEMICOL, SQBO, SQBC, PLUS, LT, DEF, DRIVERDEF, LE, EQ, GT, GE, ENDDEF, DRIVERENDDEF, NUM, RNUM, ID, AND, ARRAY, BOOLEAN, BREAK, CASE, DECLARE, DEFAULT, DRIVER, END, FOR, GET_VALUE, IN, INPUT, INTEGER, MODULE, OF, OR, PARAMETERS, PRINT, PROGRAM, REAL, RETURNS, START, SWITCH, TAKES, USE, WHILE, WITH, FALSE, TRUE, $,EPSILON
// }token_key;

typedef struct tElement{
    char tText[TTEXTSIZE];
    token_key  terminal;
    bool occupied;
}tElement;

ntElement nonTerminalHash[NTSIZE];
tElement terminalHash[TSIZE];

#endif