#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "symbolTableDef.h"


symbolTable* globalTable;

symbolTable* createSymbolTable(char* tableName, symbolTable* parentTable);
// symbolRecord* createNewRecord();
void insertIntoSymbolTable(symbolTable* table, char* name,stEntryType entryType,dType dType);
int hashingFunction(char* name);
symbolRecord* searchSymbolTable(char* recordName, symbolTable* table);
void initSymbolTable();
void main();
#endif