#include "symbolTable.h"

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
