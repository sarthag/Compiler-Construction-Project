#include "symbolTable.h"

void print_static_dynamic(symbolTable* entryTable){
    //print all the symbol tables 
    for(int i=0;i<ST_SIZE;i++){

        if(entryTable->symbTable[i]->occupied==1){
            //if the table is occupied 
            if(entryTable->symbTable[i] ->isScope==1){
                //function, conditional or iterative
                print_static_dynamic(entryTable->symbTable[i] ->scopePointer);
            }
            else {
                //primitive or array type
                if(entryTable->symbTable[i] ->entry_DT.isArray==1){
                    if(entryTable->symbTable[i] ->entry_DT.varType.arr.isDynamic){
                        
                        printf("1. Module: %s\t", entryTable->tableName);
                        printf("2. Scope: [%d, %d]\t", entryTable->scopeBeginLine, entryTable->scopeEndLine);
                        printf("3. Variable Name: %s \t", entryTable->symbTable[i]->name);
                        printf("4. Statac or dynamic: Dynamic\t");
                        printf("5. Range Variables: [%s, %s]", entryTable->symbTable[i]->entry_DT.varType.arr.lowerBound.variable, entryTable->symbTable[i]->entry_DT.varType.arr.upperBound.variable);
                        printf("6. Element Type: %s\t", d_type[entryTable->symbTable[i]->entry_DT.varType.arr.arraydType]);
        
                        // printf("Array element %s is of Type %d with lower bound %s and upper bound %s and width %d and offset %d \n", 
                        // entryTable->symbTable[i] ->name, entryTable->symbTable[i] ->entry_DT.varType.arr.arraydType,
                        // entryTable->symbTable[i] -> entry_DT.varType.arr.lowerBound.variable, entryTable->symbTable[i] ->entry_DT.varType.arr.upperBound.variable,entryTable->symbTable[i]->width,entryTable->symbTable[i]->offset);

                    }
                    else{
                        printf("1. Module: %s\t", entryTable->tableName);
                        printf("2. Scope: [%d, %d]\t", entryTable->scopeBeginLine, entryTable->scopeEndLine);
                        printf("3. Variable Name: %s \t", entryTable->symbTable[i]->name);
                        printf("4. Statac or dynamic: Static\t");
                        printf("5. Range Index: [%d, %d]", entryTable->symbTable[i]->entry_DT.varType.arr.lowerBound.bound, entryTable->symbTable[i]->entry_DT.varType.arr.upperBound.bound);
                        printf("6. Element Type: %s\t", d_type[entryTable->symbTable[i]->entry_DT.varType.arr.arraydType]);
        
                        // printf("Array element %s is of Type %d with lower bound %d and upper bound %d width %d and offset %d  \n", 
                        // entryTable->symbTable[i] ->name, entryTable->symbTable[i] ->entry_DT.varType.arr.arraydType,
                        // entryTable->symbTable[i] -> entry_DT.varType.arr.lowerBound.bound, entryTable->symbTable[i] ->entry_DT.varType.arr.upperBound.bound,entryTable->symbTable[i]->width,entryTable->symbTable[i]->offset);
                        

                    }
                    
                }
                else{
                    // variable
                    continue;
                    // printf("Variable %s is of Type %d width %d and offset %d \n", entryTable->symbTable[i] ->name, 
                    // entryTable->symbTable[i] ->entry_DT.varType.primitiveType,entryTable->symbTable[i]->width,entryTable->symbTable[i]->offset);
                }
                
            }
        }
    }
    printf("Finished printing the symbol table %s\n", entryTable->tableName);
}


void printAllSD(symbolTable* table){
    printf("Printing The Symbol Table\n");
    print_static_dynamic(table);
}