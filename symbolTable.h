#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "symbolTableDef.h"

/*
Pass 1 : Adding names and type to the symbol table

Pass 2 : Go back and add offset and width 

*/

symbolTable* createSymbolTable(char* tableName, symbolTable* parentTable);
// symbolRecord* createNewRecord();
symbolRecord* insertIntoSymbolTable(symbolTable* table, char* name,stEntryType entryType, dType entrydType);
symbolRecord* insertIntoSymbolTableArr(symbolTable* table, char* name,vartype vt);
int hashingFunction(char* name);
symbolRecord* searchSymbolTable(char* recordName, symbolTable* table);
entryDataType gettypeFromtid(astNode* astnode,symbolTable* table);
void initSymbolTable();
void generateSTpass1(astNode* treeRoot, symbolTable* homeTable);
void generateSTpass2(astNode* treeRoot, symbolTable* homeTable);
symbolTable* insertSTSwitch(astNode* node, symbolTable* table);

#endif