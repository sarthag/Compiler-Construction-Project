#include "symbolTable.h"

void staticTypeChecking(astNode * current, symbolTable * table){
    if(current->nodeType == TERMINAL){
        switch (current->name.t.tid)
        {
        case 10:
            if(current->leftChild->name.t.tid == ID){
                entryDataType locationTypeLHS = searchSymbolTable(current->leftChild->pt->element.t.lexeme, table)->entry_DT;
                if(locationTypeLHS.isArray == 0){
                    if(current->leftChild->rightSibling->name.t.tid == ID){
                        entryDataType locationTypeRHS = searchSymbolTable(current->leftChild->rightSibling->pt->element.t.lexeme, table)->entry_DT;
                        if(locationTypeRHS.isArray == 0){
                            if(locationTypeLHS.varType.primitiveType == locationTypeRHS.varType.primitiveType){
                                return gettypeFromtid(current->leftChild, globalTable).varType.primitiveType;
                            }
                            else{
                                printf("type mismatch");
                                return;
                            }
                        }
                    }
                    else if (current->leftChild->rightSibling->name.t.tid == NUM){

                    }
                }
            }
            else{
                printf("assigning to  non-variable entity");
            }
            break;
        case 7:
            if (current->leftChild->name.t.tid == NUM && current->leftChild->rightSibling->name.t.tid == NUM){
                break;
            }
            else if (current->leftChild->name.t.tid == ID && current->leftChild->rightSibling->name.t.tid == NUM){
                entryDataType locationTypeLHS = searchSymbolTable(current->leftChild->pt->element.t.lexeme, table)->entry_DT;
                if(locationTypeLHS.isArray == 1){
                    
                }
                else if (locationTypeLHS.isArray == 0){
                    if(locationTypeLHS.varType.primitiveType == NUM){
                        break;
                    }
                    else{
                        printf("Type Error: expecting INTEGER");
                    }
                }
            }
            else if (current->leftChild->name.t.tid == NUM && current->leftChild->rightSibling->name.t.tid == ID){
                entryDataType locationTypeRHS = searchSymbolTable(current->leftChild->rightSibling->pt->element.t.lexeme, table)->entry_DT;
                if(locationTypeRHS.isArray == 1){
                    
                }
                else if (locationTypeRHS.isArray == 0){
                    if(locationTypeRHS.varType.primitiveType == NUM){
                        break;
                    }
                    else{
                        printf("Type Error: expecting INTEGER");
                    }
                }
            }
            else if (current->leftChild->name.t.tid == ID && current->leftChild->rightSibling->name.t.tid == ID){
                entryDataType locationTypeRHS = searchSymbolTable(current->leftChild->rightSibling->pt->element.t.lexeme, table)->entry_DT;
                entryDataType locationTypeLHS = searchSymbolTable(current->leftChild->pt->element.t.lexeme, table)->entry_DT;
                if(locationTypeRHS.isArray == 1){
                    
                }
                else if (locationTypeRHS.isArray == 0 && locationTypeLHS.isArray == 0){
                    if(locationTypeLHS.varType.primitiveType == NUM && locationTypeRHS.varType.primitiveType == NUM){
                        break;
                    }
                    else{
                        printf("Type Error: expecting INTEGER");
                    }
                }
            }
            else{
                rintf("Type Error: expecting INTEGER");
            }
        
        default:
            break;
        }
    }
}
