#ifndef ICGENERATION_H 
#define ICGENERATION_H 

#include "icGenerationDef.h"
symbolRecord* insertIntoTempTable(symbolTable * parentTable, entryDataType tempType);
symbolRecord* findFromST(char* recordName, symbolTable* table);
void createICG(astNode* node, symbolTable* table);
void generateIC();

int tempVarCounter;

#endif