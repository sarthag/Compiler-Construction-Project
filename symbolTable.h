#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "symbolTableDef.h"

/*
Pass 1 : Adding names and type to the symbol table

Pass 2 : Go back and add offset and width 

*/

symbolTable* createSymbolTable(char* tableName, symbolTable* parentTable);
// symbolRecord* createNewRecord();
symbolRecord* insertIntoSymbolTable(symbolTable* table, char* name,stEntryType entryType,dType entrydType);
symbolRecord* insertIntoSymbolTableArr(symbolTable* table, char* name,int lowerBound, int upperBound, dType arrType);
int hashingFunction(char* name);
symbolRecord* searchSymbolTable(char* recordName, symbolTable* table);
void initSymbolTable();
void generateST(astNode* root, symbolTable* table);
symbolTable* insertSTSwitch(astNode* node, symbolTable* table);

#endif