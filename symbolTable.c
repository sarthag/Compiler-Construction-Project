#include "symbolTable.h"

symbolTable* createSymbolTable(char* tableName, symbolTable* parentTable){
    symbolTable* newTable = (symbolTable*)malloc(sizeof(symbolTable));
    newTable->parentTable = parentTable;
    newTable->firstEntry=NULL;
    newTable->lastEntry = NULL;
    newTable->tableName=tableName;
}

symbolRecord* createNewRecord(){
    //create and return a new record 
}
void insertIntoSymbolTable(symbolTable* table, symbolRecord* record){
    //record has been created and is only being inserted to the table 
    if(table->firstEntry==NULL){
        table->firstEntry = record;
    }
    else{
        table->lastEntry->nextEntry = record;
        table->lastEntry = record;
    }
}

int hashingFunction(char* name){

}

symbolRecord* searchSymbolTable(char* recordName){

}

void initSymbolTable(){
    globalTable = createSymbolTable("global", NULL);
}

void main(){
    initSymbolTable();
}