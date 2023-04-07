#include "symbolTable.h"

symbolTable* createSymbolTable(char* tableName, symbolTable* parentTable){
    symbolTable* newTable = (symbolTable*)malloc(sizeof(symbolTable));
    newTable->parentTable = parentTable;
    // newTable->firstEntry=NULL;
    // newTable->lastEntry = NULL;
    newTable->tableName=tableName;
    return newTable;
}


//Make dType NA for iterative and conditional
void insertIntoSymbolTable(symbolTable* table, char* name,stEntryType entryType,dType dType){
    int i = 0;
    int hash = hashingFunction(name);
    int index = hash % ST_SIZE;
    char* tableName;
    while(table->symbTable[index].occupied == true){
        i++;
        index  = (hash + (i*i))%ST_SIZE;

    }//open addressing incase of collision

    //assigning values
    strcpy(table ->symbTable[index].name, name);
    table ->symbTable[index].entryType = entryType;
    //if it is a VARIABLE then we create no new table but if it is not then we create a new symbol table
    if(entryType == VARIABLE){
       table ->symbTable[index].isScope = 0; 
       
    } 
    else{
        table -> symbTable[index].isScope = 1;
        table ->nextTable = createSymbolTable(name,table);
    }
    table ->symbTable[index].type = dType;
    table -> symbTable[index].occupied = true;
}

int hashingFunction(char* name){
    long long prime = PRIME;
    long long hashVal = 0;
    long long primePower = 1;
    long long mod = MOD;
    int size = strlen(name);
    for(int i = 0  ; i < size ; i++){
        hashVal = (hashVal + ((name[i]-'a'+1)*primePower)) % mod;
        primePower = (primePower + 1) % mod;
    }

    return hashVal;

}
//this function just specifically searches a given symbol table not all the symbol tables we'll make another function for that
symbolRecord* searchSymbolTable(char* recordName, symbolTable* table){
    int i = 0;
    int hashValue = hashingFunction(recordName);
    int index = hashValue % ST_SIZE;
    while (table -> symbTable[index].occupied){
        if(strcmp(recordName, table -> symbTable[index].name) == 0){
            return &table -> symbTable[index]; //returning address of entry
        }
        i++;
        index  = (hashValue + (i*i))%KTSIZE;
    }
    return NULL;

}

void initSymbolTable(){
    globalTable = createSymbolTable("global", NULL);
}

void main(){
    initSymbolTable();
}