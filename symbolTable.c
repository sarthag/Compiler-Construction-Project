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
symbolRecord* insertIntoSymbolTable(symbolTable* table, char* name,stEntryType entryType, dType entrydType){
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
    table ->symbTable[index].entry_DT.isArray = false;
    table ->symbTable[index].entry_DT.varType.primitiveType = entrydType;
    table -> symbTable[index].occupied = true;
    return table;
}


void insertIntoSymbolTableArr(symbolTable* table, char* name,vartype vt){

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
    table ->symbTable[index].entry_DT.isArray = true;
    table ->symbTable[index].entry_DT.varType.arr.arraydType = vt.arr.arraydType;
    table ->symbTable[index].entry_DT.varType.arr.lowerBound = vt.arr.lowerBound;
    table ->symbTable[index].entry_DT.varType.arr.upperBound = vt.arr.upperBound;
    table ->symbTable[index].occupied = true;

}


int hashingFunction(char* name){
    long long prime = PRIME;
    long long hashVal = 0;
    long long primePower = 1;
    long long mod = MOD;
    int size = strlen(name);
    for(int i = 0  ; i < size ; i++){
        hashVal = (hashVal + ((name[i]-'0'+1)*primePower)) % mod;
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
    generateST(syntaxTree->root, globalTable);
}


void generateST(astNode* treeRoot, symbolTable* table){
    astNode* root = treeRoot;
    root = root->leftChild; 

    while(root != NULL){
        table = insertSTSwitch(root, table);
        generateST(root, table);
        root = root->rightSibling;
    }
    return;
}
entryDataType gettypeFromtid(astNode* astnode,symbolTable* table){
    entryDataType edt;

    switch(astnode->name.t.tid){
                case INTEGER:
                    edt.isArray = false;
                    edt.varType.primitiveType = INT_DT;
                    break;
                case REAL:
                    edt.isArray = false;
                    edt.varType.primitiveType  = REAL_DT;
                    break;
                case BOOLEAN:
                    edt.isArray = false;
                    edt.varType.primitiveType  = BOOL_DT;
                    break;
                case ARRAY:
                    //need to take care of ID type
                    edt.isArray = true;
                    vartype varType;
                    varType.arr.arraydType = gettypeFromtid(astnode ->leftChild -> rightSibling,table).varType.primitiveType;
                    int lbSign = 1;
                    int rbSign = 1;
                    int lb;
                    int rb;
                    if(astnode->leftChild->name.t.tid == MINUS){
                        lbSign = -1;
                    }
                    if(astnode->leftChild->rightSibling->name.t.tid == MINUS){
                        rbSign = -1;
                    }
                    lb = lbSign*(astnode -> leftChild ->leftChild->name.t.num);
                    rb = rbSign*(astnode -> leftChild ->rightSibling->name.t.num);
                    edt.varType.arr.lowerBound = lb;
                    edt.varType.arr.upperBound = rb;
                    insertIntoSymbolTableArr(table,astnode->name.t.lexeme,varType);
                    

                    
                    break;

                    
                //ARRAY case yet to be implemented
    
    }
    return edt;

}

symbolTable* insertSTSwitch(astNode* node, symbolTable* table){

    //search to check if it already exists in one of the tables 
    if(searchSymbolTable(node->name.t.lexeme, table) !=NULL){
        printf("ERROR: Redeclaration of a variable \n ");
        return;
    }
    //need to make the rule nos 0 indexed
    int rule = node->rule_no + 1;
    switch (rule){
    case 4:
        symbolRecord* record = insertIntoSymbolTable(table, node->name.t.lexeme, FUNCTION, NA);  
        // insertSTSwitch(node -> , record ->scopePointer);  
        return table;
        //FIGURE OUT FUNCTION DATATYPE    
        break;
    
    case 7:
        symbolRecord* record = searchSymbolTable(node ->name.t.lexeme,table);
        return record ->scopePointer;
        break;
    
    case 8:
        symbolRecord* record = searchSymbolTable(node ->name.t.lexeme,table);
        return record ->scopePointer;
        break; 

    case 10:
        insertIntoSymbolTable(table, node-> name.t.lexeme,FUNCTION,NA);
        break; 
    
    case 12:
        dType datatype;
        astNode* astListnode = node -> leftChild;
        while(astListnode -> name.t.tid != EPSILON){
            datatype = gettypeFromtid(astListnode ->leftChild->name.t.tid,table).varType.primitiveType;
            insertIntoSymbolTable(table,node -> name.t.lexeme,VARIABLE,datatype);
            astListnode = astListnode -> rightSibling;
        }
        return table;
        break; 

    case 15: 
        dType datatype;
        astNode* astListnode = node -> leftChild;
        while(astListnode -> name.t.tid != EPSILON){
            datatype = gettypeFromtid(node ->leftChild -> rightSibling->name.t.tid,table).varType.primitiveType;
            insertIntoSymbolTable(table,node -> name.t.lexeme,VARIABLE,datatype);
            astListnode = astListnode -> rightSibling;

        }
        return table;

        break;
    case 22:
        
        
        return table;
        break;
    case 68:
    //depends on the AST for the logic first get datatype and then iterate 
        break; 

    case 69: 
    //depends on the AST for the logic first get datatype and then iterate 
        break; 

    case 124: 
        dType datatype;
        arrayType arrType;
        bool isArrayType;
        datatype = gettypeFromtid(node ->leftChild -> rightSibling->name.t.tid,table).varType.primitiveType;
        astNode* idListnode  = node -> leftChild -> leftChild;
        while(idListnode -> name.t.tid != EPSILON){
            insertIntoSymbolTable(table,node -> name.t.lexeme,VARIABLE,datatype);
            idListnode = idListnode ->rightSibling;
        } 

        return table;
    //depends on the AST for the logic first get datatype and then iterate 
        break; 

    case 125:
        sprintf(counterStr, "%d", counter);
        symbolRecord* record = insertIntoSymbolTable(table, counterStr, CONDITIONAL, NA);
        // insertSTSwitch(node -> ,record ->scopePointer);
        counter++;
        return record -> scopePointer;
        break; 

    case 134:
        sprintf(counterStr, "%d", counter);
        symbolRecord* record = insertIntoSymbolTable(table, counterStr, ITERATIVE, NA);
        // insertSTSwitch(node -> ,record ->scopePointer);
        counter++;
        return record -> scopePointer;
        break; 

    case 135: 
        sprintf(counterStr, "%d", counter);
        symbolRecord* record = insertIntoSymbolTable(table, counterStr, ITERATIVE, NA);
        // insertSTSwitch(node -> ,record ->scopePointer);
        counter++;
        return record -> scopePointer;
        break; 

    default:
        return table;
        break;
    }

}

void printSymbolTables(symbolTable* entryTable){
    //print all the symbol tables 
    for(int i=0;i<ST_SIZE;i++){

        if(entryTable->symbTable[i].occupied==1){
            //if the table is occupied 
            if(entryTable->symbTable[i].isScope==1){
                //function, conditional or iterative
                printf("\n\n Printing Symbol Table of %s \n ", entryTable->symbTable[i].name);
                printSymbolTables(entryTable->symbTable[i].scopePointer);
            }
            else {
                //primitive or array type
                if(entryTable->symbTable[i].entry_DT.isArray==1){
                    printf("Array element %s is of Type %d with lower bound %d and upper bound %d \n", 
                    entryTable->symbTable[i].name, entryTable->symbTable[i].entry_DT.varType.arr.arraydType,
                    entryTable->symbTable[i].entry_DT.varType.arr.lowerBound, entryTable->symbTable[i].entry_DT.varType.arr.upperBound);
                }
                else{
                    printf("Variable %s is of Type %d \n", entryTable->symbTable[i].name, 
                    entryTable->symbTable[i].entry_DT.varType.primitiveType);
                }
                
            }
        }
    }

    printf("Finished printing the table \n");
    
}

void main(){
    initSymbolTable();
    generateST(syntaxTree->root, globalTable);
    printSymbolTables(globalTable);
}