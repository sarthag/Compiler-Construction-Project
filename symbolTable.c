#include "symbolTable.h"

symbolTable* createSymbolTable(char* tableName, symbolTable* parentTable){
    symbolTable* newTable = (symbolTable*)malloc(sizeof(symbolTable));
    newTable->parentTable = parentTable;
    // newTable->firstEntry=NULL;
    // newTable->lastEntry = NULL;
    newTable->tableName=tableName;
    return newTable;
}

//Make separate functions and write the code to go through our ast and then call one of the functions depending on the label
//Make dType NA for iterative and conditional
void insertIntoSymbolTable(symbolTable* table, char* name,stEntryType entryType,dType entrydType){
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
        table -> symbTable[index].scopePointer = createSymbolTable(name,table);
    }
    table ->symbTable[index].isArray = false;
    table ->symbTable[index].varType.primitiveType = entrydType;
    table -> symbTable[index].occupied = true;
}

void insertIntoSymbolTableArr(symbolTable* table, char* name,int lowerBound, int upperBound, dType arrType){
    int i = 0;
    int hash = hashingFunction(name);
    int index = hash % ST_SIZE;
    char* tableName;
    while(table->symbTable[index].occupied == true){
        i++;
        index  = (hash + (i*i))%ST_SIZE;
        
    }
    strcpy(table ->symbTable[index].name, name);
    bool isArray = true;
    bool isScope = false;
    table ->symbTable[index].entryType = VARIABLE;
    table ->symbTable[index].varType.arr.arraydType = arrType;
    table ->symbTable[index].varType.arr.lowerBound = lowerBound;
    table ->symbTable[index].varType.arr.upperBound = upperBound;
    table ->symbTable[index].occupied = true;

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