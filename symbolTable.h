// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "symbolTableDef.h"

/*
Pass 1 : Adding names and type to the symbol table

Pass 2 : Go back and add offset and width 

*/

dType staticTypeChecking(astNode * current, symbolTable * table);
symbolTable* createSymbolTable(char* tableName, symbolTable* parentTable);
symbolRecord* insertIntoSymbolTable(symbolTable* table, char* name,stEntryType entryType, entryDataType entrydType);
symbolRecord* insertIntoSymbolTableArr(symbolTable* table, char* name,entryDataType entryDt);
symbolRecord* searchSymbolTable(char* recordName, symbolTable* table);
symbolRecord* searchAllSymbolTable(char* recordName, symbolTable* table);
void initSymbolTable(astNode* node);
void initSymbolTablewithTC(astNode* node);
int hashingFunction(char* name);
void generateSTpass1(astNode* treeRoot, symbolTable* homeTable);
void generateSTpass1withTC(astNode* treeRoot, symbolTable* homeTable);
void generateSTpass2(astNode* treeRoot, symbolTable* homeTable);
entryDataType gettypeFromtid(astNode* astnode,symbolTable* table);
void incrementOffset(symbolTable*table, entryDataType edt, int index);
symbolTable* insertSTSwitch(astNode* node, symbolTable* table);
void printSymbolTables(symbolTable* entryTable);
void printAllST(symbolTable* table);
dType checkRel(astNode * current, symbolTable * table);
dType checkBool(astNode * current, symbolTable * table);
dType staticTypeChecking(astNode * current, symbolTable * table);
void matchInputParams(char* funcName, astNode* inputParams);
void matchReturnParams(astNode* assignParams, char* funcName);
void checkNestedFunctionCall(symbolTable* funcST);
#endif