#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "symbolTableDef.h"

/*
Pass 1 : Adding names and type to the symbol table

Pass 2 : Go back and add offset and width 

*/


symbolTable* createSymbolTable(char* tableName, symbolTable* parentTable);
symbolRecord* insertIntoSymbolTable(symbolTable* table, char* name,stEntryType entryType, entryDataType entrydType);
symbolRecord* insertIntoSymbolTableArr(symbolTable* table, char* name,entryDataType entryDt);
symbolRecord* searchSymbolTable(char* recordName, symbolTable* table);
symbolRecord* searchAllSymbolTable(char* recordName, symbolTable* table);
void initSymbolTable();
int hashingFunction(char* name);
void generateSTpass1(astNode* treeRoot, symbolTable* homeTable);
void generateSTpass2(astNode* treeRoot, symbolTable* homeTable);
entryDataType gettypeFromtid(astNode* astnode,symbolTable* table);
void incrementOffset(symbolTable*table, entryDataType edt, int index);
symbolTable* insertSTSwitch(astNode* node, symbolTable* table);
void printSymbolTables(symbolTable* entryTable);
#endif