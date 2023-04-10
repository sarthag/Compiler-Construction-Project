#include "symbolTable.h"

symbolTable* createSymbolTable(char* tableName, symbolTable* parentTable){
    symbolTable* newTable = (symbolTable*)malloc(sizeof(symbolTable));
    newTable->parentTable = parentTable;
    newTable -> latestOffset = 0;
    if(parentTable == NULL){
        newTable->nestingLevel = 0;
    }

    else{
        newTable -> nestingLevel = parentTable -> nestingLevel + 1;
    }
    newTable->tableName=tableName;
    return newTable;
}

//Make separate functions and write the code to go through our ast and then call one of the functions depending on the label
//Make dType NA for iterative and conditional
symbolRecord* insertIntoSymbolTable(symbolTable* table, char* name,stEntryType entryType, entryDataType entrydType){
    
    symbolRecord* searchRecord = searchSymbolTable(name, table);
    if (searchRecord != NULL){
        printf("ERROR: Redeclaration of record"); 
        return searchRecord;
    }
    
    int i = 0;
    int hash = hashingFunction(name);
    int index = hash % ST_SIZE;
    char* tableName;


    while(table->symbTable[index] ->occupied == true){
        i++;
        index  = (hash + (i*i))%ST_SIZE;

    }//open addressing incase of collision

    //assigning values
    strcpy(table ->symbTable[index]->name, name);
    table ->symbTable[index]->entryType = entryType;
    //if it is a VARIABLE then we create no new table but if it is not then we create a new symbol table
    if(entryType == VARIABLE){
       table ->symbTable[index] ->isScope = 0;
       table -> symbTable[index]->offset = table ->latestOffset;
       incrementOffset(table, entrydType, index);
       
       
    }
    else{
        table -> symbTable[index] -> isScope = 1;
        table -> symbTable[index] -> scopePointer = createSymbolTable(name,table);
    }
    table ->symbTable[index] -> entry_DT.isArray = false;
    table ->symbTable[index] -> entry_DT.varType.primitiveType = entrydType.varType.primitiveType;
    table -> symbTable[index] -> occupied = true;
    table -> symbTable[index] ->isFuncDef = false;
    table -> symbTable[index] ->funcCall = false;
    return table -> symbTable[index];
}


symbolRecord* insertIntoSymbolTableArr(symbolTable* table, char* name,entryDataType entryDt){

    int i = 0;
    int hash = hashingFunction(name);
    int index = hash % ST_SIZE;
    char* tableName;
    while(table->symbTable[index] -> occupied == true){
        i++;
        index  = (hash + (i*i))%ST_SIZE;
        
    }
    strcpy(table ->symbTable[index] ->name, name);
    bool isArray = true;
    bool isScope = false;
    table ->symbTable[index] ->entryType = VARIABLE;
    table ->symbTable[index] ->entry_DT.isArray = true;
    table ->symbTable[index] ->entry_DT.varType.arr.arraydType = entryDt.varType.arr.arraydType;
    table ->symbTable[index] ->entry_DT.varType.arr.lowerBound = entryDt.varType.arr.lowerBound;
    table ->symbTable[index] ->entry_DT.varType.arr.upperBound = entryDt.varType.arr.upperBound;
    table ->symbTable[index] ->occupied = true;
    table ->symbTable[index] ->offset = table->latestOffset;
    incrementOffset(table, entryDt, index);
    return table -> symbTable[index];
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
    while (table -> symbTable[index] ->occupied){
        if(strcmp(recordName, table -> symbTable[index] ->name) == 0){
            return table -> symbTable[index]; //returning address of entry
        }
        i++;
        index  = (hashValue + (i*i))%KTSIZE;
    }
    return NULL;

}

void initSymbolTable(){
    globalTable = createSymbolTable("global", NULL);
    generateSTpass1(syntaxTree->root, globalTable);
    generateSTpass2(syntaxTree->root, globalTable);
}


void generateSTpass1(astNode* treeRoot, symbolTable* homeTable){ // SHRAYES CHECK

    if(treeRoot->name.t.tid == USE){
        return; 
    }

    astNode* root = treeRoot;
    symbolTable* table = homeTable;
    root = root->leftChild; 

    while(root != NULL){
        table = insertSTSwitch(root, table);
        generateSTpass1(root, table);
        root = root->rightSibling;
    }
    return;
}


void generateSTpass2(astNode* treeRoot, symbolTable* homeTable){  // THIS IS WRONG NEED TO FIX SHRAYES
    if(treeRoot->name.t.tid != USE){
        return; 
    }

    astNode* root = treeRoot;
    symbolTable* table = homeTable;
    root = root->leftChild; 

    while(root != NULL){
        table = insertSTSwitch(root, table);
        generateSTpass2(root, table);
        root = root->rightSibling;
    }
    return;
}


entryDataType gettypeFromtid(astNode* astnode, symbolTable* table){
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
            edt.varType.arr.arraydType = gettypeFromtid(astnode ->leftChild -> rightSibling,table).varType.primitiveType;
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
            insertIntoSymbolTableArr(table,astnode->name.t.lexeme,edt);
            break;
    }
    return edt;
}

void incrementOffset(symbolTable*table, entryDataType edt, int index){
    table->symbTable[index]->width = 0; 
    table->symbTable[index]->offset = table->latestOffset;

    if(edt.isArray){
        int arrSize = edt.varType.arr.upperBound - edt.varType.arr.lowerBound + 1 ;
        table->symbTable[index]->width += ARRAY_WIDTH_EXTRA;

        switch(edt.varType.arr.arraydType){
            case INT_DT :
                table->symbTable[index]->width += arrSize*(INT_WIDTH);
                break;
            case REAL_DT:
                table->symbTable[index]->width += arrSize*(REAL_WIDTH);
                break;
            case BOOL_DT:
                table->symbTable[index]->width += arrSize*(BOOL_WIDTH);
                break;
            default:
                break;
        }

        
    }

    else{
        table->symbTable[index]->offset = table->latestOffset;
        switch(edt.varType.primitiveType){
            case INT_DT :
                table->symbTable[index]->width += INT_WIDTH;
                break;
            case REAL_DT:
                table->symbTable[index]->width += REAL_WIDTH;
                break;
            case BOOL_DT:
                table->symbTable[index]->width += BOOL_WIDTH;
                break;
            default:
                break;
        }  
    }

    table->latestOffset += table->symbTable[index]->width;
}

symbolTable* insertSTSwitch(astNode* node, symbolTable* table){
    
    //search to check if it already exists in one of the tables 
    if(searchSymbolTable(node->name.t.lexeme, table) !=NULL){
        printf("ERROR: Redeclaration of a variable \n ");       //SHRAYES CHECK
        return NULL;
    }
    //variables for switch case
    symbolRecord* record;
    astNode* astListnode;
    entryDataType entrydt;

    //need to make the rule nos 0 indexed
    int rule = node->rule_no + 1;
    switch (rule){
    case 4:
        entrydt.isArray = false; 
        entrydt.varType.primitiveType = NA;
        record = insertIntoSymbolTable(table, node->name.t.lexeme, FUNCTION, entrydt);  
 
        return table;
        //FIGURE OUT FUNCTION DATATYPE    
        break;
    
    case 7:
        record = searchSymbolTable(node ->name.t.lexeme,table);
        record -> isFuncDef = true;
        // Get input plist and output plist here SHRAYES
        return record ->scopePointer;
        break;
    
    case 8:
        record = searchSymbolTable(node ->name.t.lexeme,table);
        return record ->scopePointer;
        break; 

    case 10:
        entrydt.isArray = false; 
        entrydt.varType.primitiveType = NA;
        insertIntoSymbolTable(table, node-> name.t.lexeme,FUNCTION,entrydt);
        break; 
    
    case 12:
        astListnode = node -> leftChild;
        entrydt.isArray = false; 
        entrydt.varType.primitiveType = NA;
        while(astListnode -> name.t.tid != EPSILON){
            entrydt = gettypeFromtid(astListnode ->leftChild,table);
            insertIntoSymbolTable(table,node -> name.t.lexeme, VARIABLE, entrydt);

            astListnode = astListnode -> rightSibling;
        }
        return table;
        break; 

    case 15: 
        astListnode = node -> leftChild;
        entrydt.isArray = false; 
        entrydt.varType.primitiveType = NA;
        while(astListnode -> name.t.tid != EPSILON){
            entrydt = gettypeFromtid(node ->leftChild -> rightSibling,table);
            insertIntoSymbolTable(table,node -> name.t.lexeme,VARIABLE,entrydt);
            astListnode = astListnode -> rightSibling;

        }
        return table;
        break;
    
    case 56: 
        record = searchSymbolTable(node ->name.t.lexeme,table);
        record->funcCall = true; // SHRAYES CHECK
        return record ->scopePointer;
        break; 


    case 124:  
        entrydt = gettypeFromtid(node ->leftChild -> rightSibling,table);
        astNode* idListnode  = node -> leftChild -> leftChild;
        while(idListnode -> name.t.tid != EPSILON){
            if(entrydt.isArray){
                insertIntoSymbolTableArr(table,node->name.t.lexeme,entrydt);
            }
            else{
                insertIntoSymbolTable(table,node -> name.t.lexeme,VARIABLE,entrydt);
            }
            
            idListnode = idListnode ->rightSibling;
        } 

        return table;
    //depends on the AST for the logic first get datatype and then iterate 
        break; 

    case 125:
        sprintf(counterStr, "switch_%d", counter);
        entrydt.isArray = false; 
        entrydt.varType.primitiveType = NA;
        record = insertIntoSymbolTable(table, counterStr, CONDITIONAL, entrydt);
        // insertSTSwitch(node -> ,record ->scopePointer);
        counter++;
        return record -> scopePointer;
        break; 

    case 134:
        sprintf(counterStr, "for_%d", counter);
        entrydt.isArray = false; 
        entrydt.varType.primitiveType = NA;
        record = insertIntoSymbolTable(table, counterStr, ITERATIVE, entrydt);
        // insertSTSwitch(node -> ,record ->scopePointer);
        counter++;
        return record -> scopePointer;
        break; 

    case 135: 
        sprintf(counterStr, "while_%d", counter);
        entrydt.isArray = false; 
        entrydt.varType.primitiveType = NA;
        record = insertIntoSymbolTable(table, counterStr, ITERATIVE, entrydt);
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

        if(entryTable->symbTable[i] ->occupied==1){
            //if the table is occupied 
            if(entryTable->symbTable[i] ->isScope==1){
                //function, conditional or iterative
                printf("\n\n Printing Symbol Table of %s \n ", entryTable->symbTable[i] ->name);
                printSymbolTables(entryTable->symbTable[i] ->scopePointer);
            }
            else {
                //primitive or array type
                if(entryTable->symbTable[i] ->entry_DT.isArray==1){
                    printf("Array element %s is of Type %d with lower bound %d and upper bound %d \n", 
                    entryTable->symbTable[i] ->name, entryTable->symbTable[i] ->entry_DT.varType.arr.arraydType,
                    entryTable->symbTable[i] -> entry_DT.varType.arr.lowerBound, entryTable->symbTable[i] ->entry_DT.varType.arr.upperBound);
                }
                else{
                    printf("Variable %s is of Type %d \n", entryTable->symbTable[i] ->name, 
                    entryTable->symbTable[i] ->entry_DT.varType.primitiveType);
                }
                
            }
        }
    }

    printf("Finished printing the table \n");
}


void main(){
    initSymbolTable();
    printSymbolTables(globalTable);
}