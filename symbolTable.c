// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------

#include "symbolTable.h"

symbolTable* createSymbolTable(char* tableName, symbolTable* parentTable){
    symbolTable* newTable = (symbolTable*)malloc(sizeof(symbolTable));
    newTable->parentTable = parentTable;
    newTable -> latestOffset = 0;
    newTable->tableName = (char*)malloc(sizeof(char)*100);
    if(parentTable == NULL){
        newTable->nestingLevel = 0;
    }

    else{
        newTable -> nestingLevel = parentTable -> nestingLevel + 1;
    }
    for(int i = 0 ; i < ST_SIZE ; i++){
        newTable->symbTable[i] = (symbolRecord*)malloc(sizeof(symbolRecord));
        newTable -> symbTable[i]->occupied = false;
        newTable->symbTable[i]->name = (char*)malloc(sizeof(char)*100);
        newTable->symbTable[i]->isScope = false;
    }
    newTable->tableName=tableName;
    return newTable;
}
//Make separate functions and write the code to go through our ast and then call one of the functions depending on the label
//Make dType NA for iterative and conditional
symbolRecord* insertIntoSymbolTable(symbolTable* table, char* name,stEntryType entryType, entryDataType entrydType){
    printf("Inside insertIntoSymbolTable\n");
    printf("SYMBOL TABLE name:%s",name);
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
    printf("name:%s",name);
    strcpy(table ->symbTable[index]->name, name);
    printf("strcpy done \t");
    table ->symbTable[index]->entryType = entryType;
    printf("entryType done \t");
    //if it is a VARIABLE then we create no new table but if it is not then we create a new symbol table
    if(entryType == VARIABLE){
       table ->symbTable[index] ->isScope = 0; 
       table -> symbTable[index]->offset = table ->latestOffset;
       incrementOffset(table, entrydType, index);
       printf("incrementOffset done\n");
       
    }
    else{
        table -> symbTable[index] -> isScope = 1;
        table -> symbTable[index] -> scopePointer = createSymbolTable(name,table);
        printf("new st creation done\n");
    }
    table ->symbTable[index] -> entry_DT.isArray = false;
    table ->symbTable[index] -> entry_DT.varType.primitiveType = entrydType.varType.primitiveType;
    table -> symbTable[index] -> occupied = true;
    table -> symbTable[index] ->isFuncDef = false;
    table -> symbTable[index] ->isFuncDecl = false;
    table -> symbTable[index] ->funcCall = false;
    printf("Done inserting into symboltable\n");
    return table -> symbTable[index];
}


symbolRecord* insertIntoSymbolTableArr(symbolTable* table, char* name,entryDataType entryDt){
    printf("NAME:%s",name);
    printf("DTYPE:%d",entryDt.varType.primitiveType);
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
    printf("ENTERING SEARCH");
    printf("RECORD NAME: %s",recordName);
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

symbolRecord* searchAllSymbolTable(char* recordName, symbolTable* table){
    symbolRecord* search = (symbolRecord* )malloc(sizeof(symbolRecord));
    symbolTable* tempTable = table;
    search = searchSymbolTable(recordName, tempTable);
    if(search != NULL){ return search; }
    //if search returns a NULL value
    if(tempTable==globalTable){
        printf("ERROR: Undeclared record %s \n", recordName);
        return NULL;
    }
    tempTable = tempTable->parentTable;
    searchAllSymbolTable(recordName, tempTable);
}




void generateSTpass1(astNode* treeRoot, symbolTable* homeTable){ 
    printf("---Inside generateSTpass1---\n");
    if(treeRoot == NULL){
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
                    boundType lb;
                    boundType rb;
                    if(astnode->leftChild->leftChild->name.t.tid == MINUS){
                        lbSign = -1;
                    }
                    if(astnode->leftChild->leftChild ->rightSibling->name.t.tid == MINUS){
                        rbSign = -1;
                    }
                    
                    //static case sorted
                    if(astnode ->leftChild ->leftChild ->leftChild->name.t.tid == NUM && astnode ->leftChild -> leftChild ->rightSibling->leftChild ->name.t.tid == NUM){
                        edt.varType.arr.isDynamic = false;
                        lb.bound = lbSign*(astnode ->leftChild ->leftChild ->leftChild->name.t.num);
                        rb.bound = rbSign*(astnode ->leftChild -> leftChild ->rightSibling->leftChild ->name.t.num);
                        edt.varType.arr.lowerBound.bound = lb.bound;
                        edt.varType.arr.upperBound.bound = rb.bound;
                    } //dynamic type
                    else{
                        edt.varType.arr.isDynamic = true;
                        strcpy(edt.varType.arr.lowerBound.variable,astnode ->leftChild ->leftChild ->leftChild->pt->element.t.lexeme);
                        strcpy(edt.varType.arr.upperBound.variable,astnode ->leftChild -> leftChild ->rightSibling->leftChild ->pt->element.t.lexeme);
                    }
                    
            insertIntoSymbolTableArr(table,astnode->pt->element.t.lexeme,edt);
            break;
    }
    return edt;
}
                    
void incrementOffset(symbolTable*table, entryDataType edt, int index){
    table->symbTable[index]->width = 0; 
    table->symbTable[index]->offset = table->latestOffset;

    if(edt.isArray){
        if(edt.varType.arr.isDynamic){
            table->symbTable[index]->width += ARRAY_WIDTH_EXTRA;
        }
        else{
            int arrSize = edt.varType.arr.upperBound.bound - edt.varType.arr.lowerBound.bound + 1 ;
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
    //printf("----Inside insertSTSwitch----\n");
    //search to check if it already exists in one of the tables 
    // printASTnode(node);
    // printf("BEFORE IF\n");
    // if(node ->pt ->type == TERMINAL){
    //     printASTnode(node);
    //     printf("WEIRD SHIT:%s\n",node->pt -> element.t.lexeme);
    //     if(searchSymbolTable(node->pt -> element.t.lexeme, table) !=NULL){
    //         printf("ERROR: Redeclaration of a variable \n ");       
    //         return table;
    //     }
    // }
    //variables for switch case
    symbolRecord* record;
    astNode* astListnode;
    astNode* temp;
    entryDataType entrydt;

    //need to make the rule nos 0 indexed
    int rule = node->rule_no + 1;
    printf("===============================================\n");
    printf("Rule no:%d\n",rule);
    printASTnode(node);
    printf("===============================================\n");
    switch (rule){
    case 4:
        printf("case 4");
        temp = node;
        entrydt.isArray = false; 
        entrydt.varType.primitiveType = NA;
        record = insertIntoSymbolTable(table, node->pt->element.t.lexeme, FUNCTION, entrydt);
        printf("insertedIntosymboltable\n");  
        record->isFuncDecl=true;
        return table;
        //FIGURE OUT FUNCTION DATATYPE    
        break;
    // case 5:
    //     printf("case 5");
    //     temp = node ->leftChild;
    //     while(temp->name.t.tid != EPSILON){
    //         printASTnode(temp);
    //         entrydt.isArray = false; 
    //         entrydt.varType.primitiveType = NA;
    //         printf("INSERTING : %s",temp->pt->element.t.lexeme);
    //         record = insertIntoSymbolTable(table, temp->pt->element.t.lexeme, FUNCTION, entrydt);
    //         printf("insertedIntosymboltable\n");  
    //         record->isFuncDecl=true;
    //         temp = temp ->rightSibling;


    //     }
        
    //     // printf("EXITED LOOP\n");
    //     return record->scopePointer;
    //     //FIGURE OUT FUNCTION DATATYPE    
    //     break;

    
    case 7:
        // printASTnode(node);
        record = searchSymbolTable(node ->pt ->element.t.lexeme,table);
        // printf("after searching symbol table");
        if(record == NULL){
            entrydt.isArray = false; 
            entrydt.varType.primitiveType = NA;
            record = insertIntoSymbolTable(table, node -> pt ->element.t.lexeme, FUNCTION, entrydt);
        }
        record -> isFuncDef = true;
        return record ->scopePointer;
        break;
    /*
    case 8:
        printf("The element to be search is %d \n",  node ->pt->element.nt.nid);
        record = searchSymbolTable(node ->pt -> element.t.lexeme,table);
        printf("searchsymboltable done\n");
        return record ->scopePointer;
        break; 
    */
    case 10:
        printf("CASE 10\n");
        entrydt.isArray = false; 
        entrydt.varType.primitiveType = NA;
        printf("before record \n");
        record = insertIntoSymbolTable(table, "DRIVER",FUNCTION,entrydt);
        return record ->scopePointer;
        break; 
    case 11:
        table ->scopeBeginLine = node ->leftChild->name.t.line_no;
        temp = node -> leftChild;
        while(temp ->rightSibling != NULL){
            temp = temp ->rightSibling;
        }
        table ->scopeEndLine = temp->name.t.line_no;
        return table;
        break;
    case 12:
        printASTnode(node -> leftChild);
        astListnode = node -> leftChild;
        
        entrydt.isArray = false; 
        entrydt.varType.primitiveType = NA;
        printf("TABLE:%s\n",table ->parentTable->tableName);
        symbolRecord* funcRecord = searchSymbolTable(table->tableName, table->parentTable); 
        printf("funcRecord done");
        while(astListnode -> name.t.tid != EPSILON){
            entrydt = gettypeFromtid(astListnode ->leftChild, table); // table is func table
            printf("DTYPE: %d",entrydt.varType.primitiveType);
            insertIntoSymbolTable(table, astListnode ->pt ->element.t.lexeme, VARIABLE, entrydt);

            plistNode* dataNode = (plistNode*)malloc(sizeof(plistNode));
            dataNode->entryDT = entrydt; 
            dataNode->name = node->pt -> element.t.lexeme;
            if(funcRecord->input_plist.head == NULL){
                funcRecord->input_plist.head = dataNode;
                funcRecord->input_plist.tail = dataNode;
                funcRecord->input_plist.numParams = 0;                            
            }

            else{
                funcRecord->input_plist.tail->next = dataNode; 
                funcRecord->input_plist.tail = dataNode;
            }
            funcRecord ->input_plist.numParams++;
            astListnode = astListnode -> rightSibling;
        }
        return table;
        break; 

    case 15: 
        astListnode = node -> leftChild;
        entrydt.isArray = false; 
        entrydt.varType.primitiveType = NA;
        while(astListnode -> name.t.tid != EPSILON){
            entrydt = gettypeFromtid(node ->leftChild -> rightSibling, table);
            insertIntoSymbolTable(table, node -> pt -> element.t.lexeme,VARIABLE,entrydt);

            plistNode* dataNode = (plistNode*)malloc(sizeof(plistNode));
            dataNode->entryDT = entrydt; 
            dataNode->name = node->pt->element.t.lexeme;
            if(funcRecord->output_plist.head == NULL){
                funcRecord->output_plist.head = dataNode;
                funcRecord->output_plist.tail = dataNode; 
                funcRecord->output_plist.numParams = 0;                           
            }

            else{
                funcRecord->output_plist.tail->next = dataNode; 
                funcRecord->output_plist.tail = dataNode;
            }
            funcRecord->output_plist.numParams++;
            astListnode = astListnode -> rightSibling;
        }
        return table;
        break;

    case 56: 
        record = searchSymbolTable(node ->pt->element.t.lexeme,table);
        record->funcCall = true; // NIVZZZZZ CHECK
        return record ->scopePointer;
        break;

    case 124:  
        // printASTnode(node);
        // printASTnode(node ->leftChild->rightSibling);
        
        entrydt = gettypeFromtid(node ->leftChild -> rightSibling,table);
        astNode* idListnode  = node -> leftChild -> leftChild;
        while(idListnode ->name.t.tid != EPSILON){
            printASTnode(idListnode);
            if(entrydt.isArray){
                insertIntoSymbolTableArr(table,idListnode->pt->element.t.lexeme,entrydt);
            }
            else{
                insertIntoSymbolTable(table,idListnode->pt->element.t.lexeme,VARIABLE,entrydt);
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
        record ->scopePointer->scopeBeginLine = node ->leftChild ->rightSibling->name.t.line_no;
        temp = node ->leftChild ->rightSibling;
        while(temp -> rightSibling != NULL){
            temp  = temp -> rightSibling;
        }
        record->scopePointer->scopeEndLine = temp ->name.t.line_no;
        counter++;
        return record -> scopePointer;
        break; 

    case 134:
        sprintf(counterStr, "for_%d", counter);
        entrydt.isArray = false; 
        entrydt.varType.primitiveType = NA;
        record = insertIntoSymbolTable(table, counterStr, ITERATIVE, entrydt);
        record ->scopePointer->scopeBeginLine = node ->leftChild ->rightSibling->rightSibling ->name.t.line_no;
        temp = node ->leftChild ->rightSibling -> rightSibling;
        while(temp -> rightSibling != NULL){
            temp  = temp -> rightSibling;
        }
        record->scopePointer->scopeEndLine = temp ->name.t.line_no;
        // insertSTSwitch(node -> ,record ->scopePointer);
        counter++;
        return record -> scopePointer;
        break; 

    case 135: 
        sprintf(counterStr, "while_%d", counter);
        entrydt.isArray = false; 
        entrydt.varType.primitiveType = NA;
        record = insertIntoSymbolTable(table, counterStr, ITERATIVE, entrydt);
        record ->scopePointer->scopeBeginLine = node ->leftChild ->rightSibling->name.t.line_no;
        temp = node ->leftChild ->rightSibling;
        while(temp -> rightSibling != NULL){
            temp  = temp -> rightSibling;
        }
        record->scopePointer->scopeEndLine = temp ->name.t.line_no;
        // insertSTSwitch(node -> ,record ->scopePointer);
        counter++;
        return record -> scopePointer;
        break; 

    default:
        printf("DEFAULT CASE::\n");
        return table;
        break;
    }
}
void printSymbolTables(symbolTable* entryTable){
    //print all the symbol tables 
    for(int i=0;i<ST_SIZE;i++){

        if(entryTable->symbTable[i]->occupied==1){
            //if the table is occupied 
            if(entryTable->symbTable[i] ->isScope==1){
                //function, conditional or iterative
                printf("1. Variable Name: %s \t", entryTable->symbTable[i]->name);
                printf("2. Module: %s\t", entryTable->tableName);
                printf("3. Scope: [%d, %d]\t", entryTable->scopeBeginLine, entryTable->scopeEndLine); 
                printf("4. Element Type: %s\t", st_entry_type[entryTable->symbTable[i]->entryType]);
                printf("5. Is Array: No\t");
                printf("6. Statac or dynamic: ---\t");
                printf("7. Array Range: ---\t");
                printf("8. Width: %d\t", entryTable->symbTable[i]->width);
                printf("9. Offset: %d\t", entryTable->symbTable[i]->offset);
                printf("10. Nesting Level: %d\n", entryTable->nestingLevel);
                printSymbolTables(entryTable->symbTable[i] ->scopePointer);
            }
            else {
                //primitive or array type
                if(entryTable->symbTable[i] ->entry_DT.isArray==1){
                    if(entryTable->symbTable[i] ->entry_DT.varType.arr.isDynamic){
                        printf("1. Variable Name: %s \t", entryTable->symbTable[i]->name);
                        printf("2. Module: %s\t", entryTable->tableName);
                        printf("3. Scope: [%d, %d]\t", entryTable->scopeBeginLine, entryTable->scopeEndLine); 
                        printf("4. Element Type: %s\t", d_type[entryTable->symbTable[i]->entry_DT.varType.arr.arraydType]);
                        printf("5. Is Array: Yes\t");
                        printf("6. Statac or dynamic: Dynamic\t");
                        printf("7. Array Range: 1\t");
                        printf("8. Width: 1\t");
                        printf("9. Offset: %d\t", entryTable->symbTable[i]->offset);
                        printf("10. Nesting Level: %d\n", entryTable->nestingLevel);
                        // printf("Array element %s is of Type %d with lower bound %s and upper bound %s and width %d and offset %d \n", 
                        // entryTable->symbTable[i] ->name, entryTable->symbTable[i] ->entry_DT.varType.arr.arraydType,
                        // entryTable->symbTable[i] -> entry_DT.varType.arr.lowerBound.variable, entryTable->symbTable[i] ->entry_DT.varType.arr.upperBound.variable,entryTable->symbTable[i]->width,entryTable->symbTable[i]->offset);

                    }
                    else{
                        printf("1. Variable Name: %s \t", entryTable->symbTable[i]->name);
                        printf("2. Module: %s\t", entryTable->tableName);
                        printf("3. Scope: [%d, %d]\t", entryTable->scopeBeginLine, entryTable->scopeEndLine);
                        printf("4. Element Type: %s\t", d_type[entryTable->symbTable[i]->entry_DT.varType.arr.arraydType]);
                        printf("5. Is Array: Yes\t");
                        printf("6. Statac or dynamic: Static\t");
                        printf("7. Array Range: %d\t", entryTable->symbTable[i]->entry_DT.varType.arr.upperBound.bound - entryTable->symbTable[i]->entry_DT.varType.arr.lowerBound.bound + 1);
                        printf("8. Width: %d\t", entryTable->symbTable[i]->width);
                        printf("9. Offset: %d\t", entryTable->symbTable[i]->offset);
                        printf("10. Nesting Level: %d\n", entryTable->nestingLevel);
                        // printf("Array element %s is of Type %d with lower bound %d and upper bound %d width %d and offset %d  \n", 
                        // entryTable->symbTable[i] ->name, entryTable->symbTable[i] ->entry_DT.varType.arr.arraydType,
                        // entryTable->symbTable[i] -> entry_DT.varType.arr.lowerBound.bound, entryTable->symbTable[i] ->entry_DT.varType.arr.upperBound.bound,entryTable->symbTable[i]->width,entryTable->symbTable[i]->offset);
                        

                    }
                    
                }
                else{
                    printf("1. Variable Name: %s \t", entryTable->symbTable[i]->name);
                    printf("2. Module: %s\t", entryTable->tableName);
                    printf("3. Scope: [%d, %d]\t", entryTable->scopeBeginLine, entryTable->scopeEndLine);
                    printf("4. Element Type: %s\t", d_type[entryTable->symbTable[i]->entry_DT.varType.arr.arraydType]);
                    printf("5. Is Array: No\t");
                    printf("6. Statac or dynamic: ---\t");
                    printf("7. Array Range: --- \t");
                    printf("8. Width: %d\t", entryTable->symbTable[i]->width);
                    printf("9. Offset: %d\t", entryTable->symbTable[i]->offset);
                    printf("10. Nesting Level: %d\n", entryTable->nestingLevel);
                    // printf("Variable %s is of Type %d width %d and offset %d \n", entryTable->symbTable[i] ->name, 
                    // entryTable->symbTable[i] ->entry_DT.varType.primitiveType,entryTable->symbTable[i]->width,entryTable->symbTable[i]->offset);
                }
                
            }
        }
    }
    printf("Finished printing the symbol table %s\n", entryTable->tableName);
}

void printAllST(symbolTable* table){
    printf("Printing The Symbol Table\n");
    printSymbolTables(table);
}

void initSymbolTable(astNode* node){
    counter = 0;
    globalTable = createSymbolTable("global", NULL);
    generateSTpass1(node, globalTable);
    printSymbolTables(globalTable);
    // printGlobalTable(globalTable);
    //generateSTpass2(syntaxTree->root, globalTable);
}


// // void printSymbolTables(symbolTable* entryTable){
//     //print all the symbol tables 
//     for(int i=0;i<ST_SIZE;i++){

//         if(entryTable->symbTable[i] ->occupied==1){
//             //if the table is occupied 
//             if(entryTable->symbTable[i] ->isScope==1){
//                 //function, conditional or iterative
//                 printf("\n\nPrinting Symbol Table of %s \n", entryTable->symbTable[i] ->name);
//                 printSymbolTables(entryTable->symbTable[i] ->scopePointer);
//             }
//             else {
//                 //primitive or array type
//                 if(entryTable->symbTable[i] ->entry_DT.isArray==1){
//                     if(entryTable->symbTable[i] ->entry_DT.varType.arr.isDynamic){
//                         printf("Array element %s is of Type %d with lower bound %s and upper bound %s and width %d and offset %d \n", 
//                         entryTable->symbTable[i] ->name, entryTable->symbTable[i] ->entry_DT.varType.arr.arraydType,
//                         entryTable->symbTable[i] -> entry_DT.varType.arr.lowerBound.variable, entryTable->symbTable[i] ->entry_DT.varType.arr.upperBound.variable,entryTable->symbTable[i]->width,entryTable->symbTable[i]->offset);

//                     }
//                     else{
//                         printf("Array element %s is of Type %d with lower bound %d and upper bound %d width %d and offset %d  \n", 
//                         entryTable->symbTable[i] ->name, entryTable->symbTable[i] ->entry_DT.varType.arr.arraydType,
//                         entryTable->symbTable[i] -> entry_DT.varType.arr.lowerBound.bound, entryTable->symbTable[i] ->entry_DT.varType.arr.upperBound.bound,entryTable->symbTable[i]->width,entryTable->symbTable[i]->offset);
                        

//                     }
                    
//                 }
//                 else{
//                     printf("Variable %s is of Type %d width %d and offset %d \n", entryTable->symbTable[i] ->name, 
//                     entryTable->symbTable[i] ->entry_DT.varType.primitiveType,entryTable->symbTable[i]->width,entryTable->symbTable[i]->offset);
//                 }
                
//             }
//         }
//     }
//     printf("Finished printing the symbol table %s\n", entryTable->tableName);
// }

// void printGlobalTable(symbolTable* table){
//     printf("\nPrinting global table\n");
//     for(int i = 0 ; i < ST_SIZE ; i++){
//         if(table->symbTable[i]->occupied){
//             printf("| NAME:%s | isScope:%d | entryType:%d |isOccupied:%d\n",table->symbTable[i]->name,table->symbTable[i]->isScope,table->symbTable[i]->entryType,table->symbTable[i]->occupied);
//     }
//         }
        
// }

// void initSymbolTable(astNode* node){
//     counter = 0;
//     globalTable = createSymbolTable("global", NULL);
//     generateSTpass1(node, globalTable);
//     printSymbolTables(globalTable);

//     //printing all the table entries 
//     // for(int i=0;i<ST_SIZE;i++){
//     //     printf("Entry name: %s\n", globalTable->symbTable[i]->name);
//     // }
//     // printGlobalTable(globalTable);
//     //generateSTpass2(syntaxTree->root, globalTable);
// }


// int main(){
//     astNodes = 0;
//     FILE* prog;
//     char* filename = "testOwn.txt";
//     char* parseTreeFile = "parseTree.txt";
//     // printf("read files\n");
//     removeComments(filename);
//     // printf("comments removed\n");
//     prog = readFile(filename);
//     // printf("file wo comments read\n");
//     populate_keyword_table();
//     printf("\n");
//     getNextToken(prog);
//     // printf("here\n");
//     InitializeParser();
//     // printf("here\n");
//     parse_code();
//     printf("parsing done\n");
//     //printParseTree(parseTree->root, parseTreeFile);   PRINT PARSE TREE HAS SEG FAULTS!!!!
//     printf("pt root: %s\n", nt_list[parseTree->root->element.nt.nid]);
//     syntaxStack = initAST();
//     printf("initAST()\n");
//     astNode* ASTroot = createASTNode(NON_TERMINAL, -1, parseTree->root);
//     printf("ast init \n");
//     topDownPass(ASTroot, parseTree->root, syntaxStack);    
//     printf("top down pass done\n");
//     printASTstack(syntaxStack);
//     printf("here\n");
//     callfindAction(ASTroot, syntaxStack);
//     ast_traversal(ASTroot);
//     printf("AST bottom up done\n");
//     printf("Starting symbolTable\n");
//     initSymbolTable(ASTroot);
//     // callfindAction(ASTroot, syntaxStack);
// }

dType checkRel(astNode * current, symbolTable * table){
    dType relType;
    astNode* temp = current->leftChild;
    if(temp->name.t.tid == ID){
        symbolRecord* record = searchAllSymbolTable(temp->pt->element.t.lexeme, table);
        if (record == NULL){
            printf("Undeclared variable\n");
            return ERROR;
        }
        if(record->entry_DT.isArray == 0){
            relType = record->entry_DT.varType.primitiveType;
        }
        else{
            relType = record->entry_DT.varType.arr.arraydType;
        }
    }
    else if(temp->nodeType == NON_TERMINAL){
        dType temporary = staticTypeChecking(temp->leftChild, table);
        relType = temporary;
    }
    else{
        relType = gettypeFromtid(temp, table).varType.primitiveType;
    }
    //printf("LHS type %d\n", relType);
    dType relType2;
    temp = temp->rightSibling;
    if(temp == NULL){
        printf("no rhs\n");
        return ERROR;
    }
    //printf("term? %d\n", temp->nodeType);
    if(temp->name.t.tid == ID){
        printf("is ID\n");
        symbolRecord* record = searchAllSymbolTable(temp->pt->element.t.lexeme, table);
        if (record == NULL){
            printf("Undeclared variable\n");
            return ERROR;
        }
        if(record->entry_DT.isArray == 0){
            relType2 = record->entry_DT.varType.primitiveType;
        }
        else{
            relType2 = record->entry_DT.varType.arr.arraydType;
        }
    }
    else if(temp->nodeType == NON_TERMINAL){
        //printf("is nt\n");
        dType temporary = staticTypeChecking(temp->leftChild, table);
        relType2 = temporary;
    }
    else{
        //printf("is num or rnum\n");
        relType2 = gettypeFromtid(temp, table).varType.primitiveType;
    }
    //printf("RHS type %d\n", relType2);
    if(relType == relType2){
        return BOOL_DT;
    }
    else{
        printf("Type Error\n");
        return ERROR;
    }
}

dType checkBool(astNode * current, symbolTable * table){
    dType boolType;
    astNode* temp = current->leftChild;
    if(temp->name.t.tid == ID){
        symbolRecord* record = searchAllSymbolTable(temp->pt->element.t.lexeme, table);
        if (record == NULL){
            printf("Undeclared variable\n");
            return ERROR;
        }
        if(record->entry_DT.isArray == 0){
            boolType = record->entry_DT.varType.primitiveType;
        }
        else{
            boolType = record->entry_DT.varType.arr.arraydType;
        }
    }
    else if(temp->nodeType == NON_TERMINAL){
        dType temporary = staticTypeChecking(temp->leftChild, table);
        boolType = temporary;
    }
    else{
        boolType = gettypeFromtid(temp, table).varType.primitiveType;
    }
    while(temp->rightSibling->name.t.tid != EPSILON){
        temp = temp->rightSibling;
        if(temp->leftChild->name.t.tid == ID){
            symbolRecord* record = searchAllSymbolTable(temp->pt->element.t.lexeme, table);
            if (record == NULL){
                printf("Undeclared variable\n");
                return ERROR;
            }
            if(record->entry_DT.isArray == 0){
                if (boolType == record->entry_DT.varType.primitiveType){
                    continue;
                }
                else{
                    printf("Type Error\n");
                    return ERROR;
                }
            }
            else{
                if (boolType == record->entry_DT.varType.arr.arraydType){
                    continue;
                }
                else{
                    printf("Type Error\n");
                    return ERROR;
                }
            }
        }
        else if(temp->leftChild->nodeType == NON_TERMINAL){
            if (boolType == staticTypeChecking(temp->leftChild, table)){
                continue;
            }
            else{
                printf("Type Error\n");
                return ERROR;
            }
        }
        else{
            if (boolType == gettypeFromtid(temp->leftChild, table).varType.primitiveType){
                continue;
            }
            else{
                printf("Type Error\n");
                return ERROR;
            }
        }
    }
    return BOOL_DT;
}

dType staticTypeChecking(astNode * current, symbolTable * table){
    //printf("-------inside Type Checking ------\n");
    if(current->nodeType == TERMINAL){
        //printf("terminal case %d \n", current->name.t.tid);
        switch (current->name.t.tid)
        {
        case 1:
            return checkBool(current, table);
        case 10:
            //printf("left child %d\n", current->leftChild->name.t.tid);
            if(current->leftChild->name.t.tid == ID){
                symbolRecord * recordLHS = searchAllSymbolTable(current->leftChild->pt->element.t.lexeme, table);
                //printf("found record 1\n");
                if (recordLHS == NULL){
                    printf("Undeclared variable\n");
                    return ERROR;
                }
                //printf("found record\n");
                entryDataType locationTypeLHS = recordLHS->entry_DT;
                if(locationTypeLHS.isArray == 0){
                    //printf("found non-array %d\n", current->leftChild->rightSibling->name.t.tid);
                    if(current->leftChild->rightSibling->name.t.tid == ID){
                        symbolRecord * recordRHS = searchAllSymbolTable(current->leftChild->rightSibling->pt->element.t.lexeme, table);
                        if (recordRHS == NULL){
                            printf("Undeclared variable\n");
                            return ERROR;
                        }
                        entryDataType locationTypeRHS = recordRHS->entry_DT;
                        if(locationTypeRHS.isArray == 0){
                            if(locationTypeLHS.varType.primitiveType == locationTypeRHS.varType.primitiveType){
                                return locationTypeLHS.varType.primitiveType;
                            }
                            else{
                                printf("type mismatch\n");
                                return ERROR;
                            }
                        }
                    }
                    else if (current->leftChild->rightSibling->name.t.tid == NUM){
                        if (locationTypeLHS.varType.primitiveType == INT_DT){
                            return INT_DT;
                        }
                        else{
                            printf("type mismatch\n");
                            return ERROR;
                        }
                    }
                    else if (current->leftChild->rightSibling->name.t.tid == RNUM){
                        if (locationTypeLHS.varType.primitiveType == REAL_DT){
                            return REAL_DT;
                        }
                        else{
                            printf("type mismatch\n");
                            return ERROR;
                        }
                    }
                    else if (locationTypeLHS.varType.primitiveType == staticTypeChecking(current->leftChild->rightSibling, table)){
                        return locationTypeLHS.varType.primitiveType;
                    }
                    else{
                        printf("type mismatch\n");
                        return ERROR;
                    }
                }
                else if(locationTypeLHS.isArray == 1){
                    //printf("found array entity\n");
                    if(locationTypeLHS.varType.arr.arraydType != INT_DT){
                        printf("Expected Integer as index\n");
                        return ERROR;
                    }
                    //printf("lower bound %d\n", current->rightSibling->pt->element.t.num);
                    if(locationTypeLHS.varType.arr.lowerBound.bound <= current->rightSibling->pt->element.t.num && locationTypeLHS.varType.arr.upperBound.bound >= current->rightSibling->pt->element.t.num){
                        //printf("index in bounds\n");
                        dType arrType = locationTypeLHS.varType.arr.arraydType;
                        if(current->leftChild->rightSibling->name.t.tid == ID){
                            symbolRecord * recordRHS = searchAllSymbolTable(current->leftChild->rightSibling->pt->element.t.lexeme, table);
                            if (recordRHS == NULL){
                                printf("Undeclared variable\n");
                                return ERROR;
                            }
                            entryDataType locationTypeRHS = recordRHS->entry_DT;
                            if(locationTypeRHS.isArray == 0){
                                if(arrType == locationTypeRHS.varType.primitiveType){
                                    return locationTypeLHS.varType.primitiveType;
                                }
                                else{
                                    printf("type mismatch\n");
                                    return ERROR;
                                }
                            }
                        }
                        else if (current->leftChild->rightSibling->name.t.tid == NUM){
                            if (arrType == INT_DT){
                                return INT_DT;
                            }
                            else{
                                printf("type mismatch\n");
                                return ERROR;
                            }
                        }
                        else if (current->leftChild->rightSibling->name.t.tid == RNUM){
                            if (arrType == REAL_DT){
                                return REAL_DT;
                            }
                            else{
                                printf("type mismatch\n");
                                return ERROR;
                            }
                        }
                        else if (arrType == staticTypeChecking(current->leftChild->rightSibling, table)){
                            return locationTypeLHS.varType.primitiveType;
                        }
                        else{
                            printf("type mismatch\n");
                            return ERROR;
                        }
                    }
                    else{
                        printf("Array index out of bound\n");
                        return ERROR;
                    }
                }
            }
            else{
                printf("assigning to  non-variable entity\n");
                return ERROR;
            }
            break;
        case 7:
            if (current->leftChild->name.t.tid == NUM && current->leftChild->rightSibling->name.t.tid == NUM){
                return INT_DT;
            }
            else if (current->leftChild->name.t.tid == ID && current->leftChild->rightSibling->name.t.tid == NUM){
                entryDataType locationTypeLHS = searchSymbolTable(current->leftChild->pt->element.t.lexeme, table)->entry_DT;
                if(locationTypeLHS.isArray == 1){
                    printf("Type Error: expecting INTEGER, recieved array\n");
                    return ERROR;                   
                }
                else if (locationTypeLHS.isArray == 0){
                    if(locationTypeLHS.varType.primitiveType == INT_DT){
                        return INT_DT;
                    }
                    else{
                        printf("Type Error: expecting INTEGER\n");
                        return ERROR;
                    }
                }
            }
            else if (current->leftChild->name.t.tid == NUM && current->leftChild->rightSibling->name.t.tid == ID){
                entryDataType locationTypeRHS = searchSymbolTable(current->leftChild->rightSibling->pt->element.t.lexeme, table)->entry_DT;
                if(locationTypeRHS.isArray == 1){
                    printf("Type Error: expecting INTEGER, recieved array\n");
                    return ERROR;
                }
                else if (locationTypeRHS.isArray == 0){
                    if(locationTypeRHS.varType.primitiveType == NUM){
                        return INT_DT;
                    }
                    else{
                        printf("Type Error: expecting INTEGER\n");
                        return ERROR;
                    }
                }
            }
            else if (current->leftChild->name.t.tid == ID && current->leftChild->rightSibling->name.t.tid == ID){
                symbolRecord * recordRHS = searchAllSymbolTable(current->leftChild->rightSibling->pt->element.t.lexeme, table);
                if (recordRHS == NULL){
                    printf("Undeclared variable\n");
                    return ERROR;
                }
                entryDataType locationTypeRHS = recordRHS->entry_DT;
                symbolRecord * recordLHS = searchAllSymbolTable(current->leftChild->pt->element.t.lexeme, table);
                if (recordLHS == NULL){
                    printf("Undeclared variable\n");
                    return ERROR;
                }
                entryDataType locationTypeLHS = recordLHS->entry_DT;
                if(locationTypeRHS.isArray == 1 || locationTypeLHS.isArray == 1){
                    printf("Type Error: expecting INTEGER, recieved array\n");
                    return ERROR;
                }
                else if (locationTypeRHS.isArray == 0 && locationTypeLHS.isArray == 0){
                    if(locationTypeLHS.varType.primitiveType == NUM && locationTypeRHS.varType.primitiveType == NUM){
                        return INT_DT;
                    }
                    else{
                        printf("Type Error: expecting INTEGER\n");
                        return ERROR;
                    }
                }
            }
            else{
                printf("Type Error: expecting INTEGER\n");
                return ERROR;
            }
            break;
        case 15:
            return checkRel(current, table);
        case 18:
            return checkRel(current, table);
        case 19:
            return checkRel(current, table);
        case 21:
            return checkRel(current, table);
        case 22:
            return checkRel(current, table);
        case 27:
            return checkBool(current, table);
        case 43:
            return checkBool(current, table);    
        default:
            break;
        }
    }
    else{
        //printf("non-terminal case %d \n", current->name.nt.nid);
        dType termType, factorPrimType;
        astNode* temp = current->leftChild;
        switch (current->name.nt.nid)
        {
        case 2:
            //dType termType;
            //astNode* temp = current->leftChild;
            if(temp->name.t.tid == ID){
                symbolRecord* record = searchAllSymbolTable(temp->pt->element.t.lexeme, table);
                if(record==NULL){
                    printf("Undeclared variable\n");
                    return ERROR;
                }
                if(record->entry_DT.isArray == 0){
                    termType = record->entry_DT.varType.primitiveType;
                    //printf("got non-array type\n");
                }
                else{
                    termType = record->entry_DT.varType.arr.arraydType;
                    //printf("got array type\n");
                }
            }
            else if(temp->nodeType == NON_TERMINAL){
                termType = staticTypeChecking(temp->leftChild, table);
            }
            else{
                termType = gettypeFromtid(temp, table).varType.primitiveType;
            }
            while(temp->rightSibling->name.t.tid != EPSILON){
                //printf("temp's value %s\n", temp->pt->element.t.lexeme);
                temp = temp->rightSibling;
                //printf("gone to right sibling\n");
                //printf("temp's left child %d\n", temp->leftChild->nodeType );
                //printf("temp's left child %d\n", temp->leftChild->pt->element.t.tid);
                if(temp->leftChild->name.t.tid == ID){
                    //printf("case 1\n");
                    //printf("temp's left child %s\n", temp->leftChild->pt->element.t.lexeme);
                    symbolRecord* record = searchAllSymbolTable(temp->leftChild->pt->element.t.lexeme, table);
                    //printf("got Right sibling record\n");
                    if(record==NULL){
                        printf("Undeclared variable\n");
                        return ERROR;
                    }
                    if(record->entry_DT.isArray == 0){
                        if (termType == record->entry_DT.varType.primitiveType){
                            continue;
                        }
                        else{
                            printf("Type Error\n");
                            return ERROR;
                        }
                    }
                    else{
                        if (termType == record->entry_DT.varType.arr.arraydType){
                            continue;
                        }
                        else{
                            printf("Type Error\n");
                            return ERROR;
                        }
                    }
                }
                else if(temp->leftChild->nodeType == NON_TERMINAL){
                    //printf("case 2\n");
                    if (termType == staticTypeChecking(temp->leftChild, table)){
                        continue;
                    }
                    else{
                        printf("Type Error\n");
                        return ERROR;
                    }
                }
        
                else{
                    //printf("going into else \n");
                    //printf("temp's left child %s\n", temp->leftChild->pt->element.t.lexeme);
                    if (termType == gettypeFromtid(temp->leftChild, table).varType.primitiveType){
                        continue;
                    }
                    else{
                        printf("Type Error\n");
                        return ERROR;
                    }
                }
            }
            //printf("exiting type checking\n");
            return termType;
            break;
        case 3:
            return checkBool(current, table);
            break;

        case 64:
            //dType factorPrimType = NULL;
            //astNode * temp1 = current->leftChild;
            if(temp->nodeType == TERMINAL){
                entryDataType factorType = gettypeFromtid(temp, table);
                if(factorType.isArray == 0){
                    factorPrimType = factorType.varType.primitiveType;
                }
                else{
                    factorPrimType = factorType.varType.arr.arraydType;
                }
            }
            else{
                factorPrimType = staticTypeChecking(current->leftChild, table);
            }
            while(temp->rightSibling->name.t.tid  == EPSILON){
                temp = temp->rightSibling;
                if (temp->name.t.tid == MUL){
                    if(temp->leftChild->name.t.tid == ID){
                        symbolRecord* record = searchAllSymbolTable(temp->pt->element.t.lexeme, table);
                        if(record==NULL){
                            printf("Undeclared variable\n");
                            return ERROR;
                        }
                        if(record->entry_DT.isArray == 0){
                            if (factorPrimType == record->entry_DT.varType.primitiveType){
                                continue;
                            }
                            else{
                                printf("Type Error\n");
                                return ERROR;
                            }
                        }
                        else{
                            if (factorPrimType == record->entry_DT.varType.arr.arraydType){
                                continue;
                            }
                            else{
                                printf("Type Error\n");
                                return ERROR;
                            }
                        }
                    }
                    else if(temp->leftChild->nodeType == NON_TERMINAL){
                        if (factorPrimType == staticTypeChecking(temp->leftChild, table)){
                            continue;
                        }
                        else{
                            printf("Type Error\n");
                            return ERROR;
                        }
                    }
                    else{
                        if (factorPrimType == gettypeFromtid(temp->leftChild, table).varType.primitiveType){
                            continue;
                        }
                        else{
                            printf("Type Error\n");
                            return ERROR;
                        }
                    }
                }
                else if (temp->name.t.tid == DIV){
                    factorPrimType = REAL_DT;
                }
            }
            return factorPrimType;
        default:
            return ERROR;
            break;
        }

    }
}

void matchInputParams(char* funcName, astNode* inputParams){
    symbolRecord* funcGlobalEntry= searchSymbolTable(funcName, globalTable);
    astNode* actualParaList = inputParams;
    struct plistNode* temp = funcGlobalEntry->input_plist.head;
    while(temp != NULL){
        entryDataType edt= gettypeFromtid(actualParaList, funcGlobalEntry->scopePointer);

        actualParaList= actualParaList->rightSibling;
        temp = temp->next;

        if(temp->entryDT.isArray != edt.isArray){
            printf("ERROR: Mismatch between array and non-array element\n");
        }
        if(temp->entryDT.isArray==false){
            //not array elements 
            if(temp->entryDT.varType.primitiveType != edt.varType.primitiveType){
                printf("ERROR: Datatype Mismatch in Input Paramaters (Primitive case)");
            }
        }
        else{
            //array elements
            if(temp->entryDT.varType.arr.arraydType != edt.varType.arr.arraydType){
                printf("ERROR: Datatype Mismatch in Input Paramaters (Array case) ");
            } 
        }
        //check if there is a mismatch in the number of parameters
        if(temp ==NULL && actualParaList !=NULL || temp !=NULL && actualParaList ==NULL){
            printf("ERROR: Mismatch between number of elements returned and function invokation \n");
        }
    }
    
}


//during function DEFINITION - the return parameters are matched to the parameters of function invokation
//invoke params -> idList1
void matchReturnParams(astNode* assignParams, char* funcName){
    symbolRecord* func = searchSymbolTable(funcName, globalTable);
    astNode* idListTemp = assignParams;
    struct plistNode* temp = func->output_plist.head;
    if(func->isFuncDef == true){
            while(temp != NULL){
                entryDataType edt= gettypeFromtid(idListTemp, func->scopePointer);
                if(temp->entryDT.varType.primitiveType != edt.varType.primitiveType){
                    printf("ERROR: Datatype Mismatch in return parameters \n");
                }
                
                temp = temp -> next;
                idListTemp = idListTemp->rightSibling;

                if(temp ==NULL && idListTemp !=NULL || temp !=NULL && idListTemp ==NULL){
                    printf("ERROR: Mismatch between number of elements returned and function invokation \n");
                }
            }
    }
}

void checkNestedFunctionCall(symbolTable* funcST) {
    for(int i=0; i<ST_SIZE;i++){
        if(funcST->symbTable[i]->isScope==true && funcST->symbTable[i]->entryType==FUNCTION){
            //this is a nested function 
            if(funcST->symbTable[i]->isFuncDef==true){
                if(funcST->symbTable[i]->isFuncDecl==true){
                    printf("ERROR: Redundant function Declaration. Function defenition has occured \n");
                    return;
                }
            }
        }
    }
}