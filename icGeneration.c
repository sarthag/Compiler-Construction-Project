#include "icGeneration.h"

void insertIntoTempTable(symbolTable * parentTable, dType tempType){
    if(parentTable->tempTable==NULL){
        parentTable ->tempTable = createSymbolTable("temp",parentTable);
    }
    char* tempVarName = (char*)malloc(100*sizeof(char));
    sprintf(tempVarName,"temp_%d",tempVarCounter++);
    
    insertIntoSymbolTable(parentTable -> tempTable,tempVarName,VARIABLE,tempType);

}


void generateIC(){
    tempVarCounter = 0;
    
}