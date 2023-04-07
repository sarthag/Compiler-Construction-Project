#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "symbolTableDef.h"

/*
Pass 1 : Adding names and type to the symbol table

Pass 2 : Go back and add offset and width 

*/

symbolTable* createSymbolTable(char* tableName, symbolTable* parentTable);
// symbolRecord* createNewRecord();
void insertIntoSymbolTable(symbolTable* table, char* name,stEntryType entryType,dType entrydType);
void insertIntoSymbolTableArr(symbolTable* table, char* name,int lowerBound, int upperBound, dType arrType);
int hashingFunction(char* name);
symbolRecord* searchSymbolTable(char* recordName, symbolTable* table);
void initSymbolTable();
void generateST(astNode* root, symbolTable* table);
//void insertSTSwitch(int rule_no, symbolTable* table);
#endif