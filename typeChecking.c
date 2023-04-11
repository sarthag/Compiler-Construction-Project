#include "symbolTable.h"

/*
 Terminals for type-checking: ASSIGNOP, PLUS, MINUS, MUL, DIV, LE, GE, LT, GT, EQ, NE, AND, OR, (ARRAYS for each op)
*/
dType staticTypeChecking(astNode * current, symbolTable * table){
    if(current->nodeType == TERMINAL){
        switch (current->name.t.tid)
        {
        case 10:
            if(current->leftChild->name.t.tid == ID){
                entryDataType locationTypeLHS = searchAllSymbolTable(current->leftChild->pt->element.t.lexeme, table)->entry_DT;
                if(locationTypeLHS.isArray == 0){
                    if(current->leftChild->rightSibling->name.t.tid == ID){
                        entryDataType locationTypeRHS = searchAllSymbolTable(current->leftChild->rightSibling->pt->element.t.lexeme, table)->entry_DT;
                        if(locationTypeRHS.isArray == 0){
                            if(locationTypeLHS.varType.primitiveType == locationTypeRHS.varType.primitiveType){
                                return locationTypeLHS.varType.primitiveType;
                            }
                            else{
                                printf("type mismatch");
                                return NULL;
                            }
                        }
                    }
                    else if (current->leftChild->rightSibling->name.t.tid == NUM){
                        if (locationTypeLHS.varType.primitiveType == INT_DT){
                            return INT_DT;
                        }
                        else{
                            printf("type mismatch");
                            return NULL;
                        }
                    }
                    else if (current->leftChild->rightSibling->name.t.tid == RNUM){
                        if (locationTypeLHS.varType.primitiveType == REAL_DT){
                            return REAL_DT;
                        }
                        else{
                            printf("type mismatch");
                            return NULL;
                        }
                    }
                    else if (locationTypeLHS.varType.primitiveType == staticTypeChecking(current->leftChild->rightSibling, table)){
                        return locationTypeLHS.varType.primitiveType;
                    }
                    else{
                        printf("type mismatch");
                        return NULL;
                    }
                }
                else if(locationTypeLHS.isArray == 1){
                    if(locationTypeLHS.varType.arr.arraydType != INT_DT){
                        printf("Expected Integer as index");
                        return NULL;
                    }
                    if(locationTypeLHS.varType.arr.lowerBound < current->leftChild->leftChild->pt->element.t.num && locationTypeLHS.varType.arr.upperBound > current->leftChild->leftChild->pt->element.t.num){
                        dType arrType = locationTypeLHS.varType.arr.arraydType;
                        if(current->leftChild->rightSibling->name.t.tid == ID){
                            entryDataType locationTypeRHS = searchSymbolTable(current->leftChild->rightSibling->pt->element.t.lexeme, table)->entry_DT;
                            if(locationTypeRHS.isArray == 0){
                                if(arrType == locationTypeRHS.varType.primitiveType){
                                    return locationTypeLHS.varType.primitiveType;
                                }
                                else{
                                    printf("type mismatch");
                                    return NULL;
                                }
                            }
                        }
                        else if (current->leftChild->rightSibling->name.t.tid == NUM){
                            if (arrType == INT_DT){
                                return INT_DT;
                            }
                            else{
                                printf("type mismatch");
                                return NULL;
                            }
                        }
                        else if (current->leftChild->rightSibling->name.t.tid == RNUM){
                            if (arrType == REAL_DT){
                                return REAL_DT;
                            }
                            else{
                                printf("type mismatch");
                                return NULL;
                            }
                        }
                        else if (arrType == staticTypeChecking(current->leftChild->rightSibling, table)){
                            return locationTypeLHS.varType.primitiveType;
                        }
                        else{
                            printf("type mismatch");
                            return NULL;
                        }
                    }
                    else{
                        printf("Array index out of bound");
                        return NULL;
                    }
                }
            }
            else{
                printf("assigning to  non-variable entity");
            }
            break;
        case 7:
            if (current->leftChild->name.t.tid == NUM && current->leftChild->rightSibling->name.t.tid == NUM){
                return INT_DT;
            }
            else if (current->leftChild->name.t.tid == ID && current->leftChild->rightSibling->name.t.tid == NUM){
                entryDataType locationTypeLHS = searchSymbolTable(current->leftChild->pt->element.t.lexeme, table)->entry_DT;
                if(locationTypeLHS.isArray == 1){
                    printf("Type Error: expecting INTEGER, recieved array");                   
                }
                else if (locationTypeLHS.isArray == 0){
                    if(locationTypeLHS.varType.primitiveType == INT_DT){
                        return INT_DT;
                    }
                    else{
                        printf("Type Error: expecting INTEGER");
                    }
                }
            }
            else if (current->leftChild->name.t.tid == NUM && current->leftChild->rightSibling->name.t.tid == ID){
                entryDataType locationTypeRHS = searchSymbolTable(current->leftChild->rightSibling->pt->element.t.lexeme, table)->entry_DT;
                if(locationTypeRHS.isArray == 1){
                    printf("Type Error: expecting INTEGER, recieved array");
                }
                else if (locationTypeRHS.isArray == 0){
                    if(locationTypeRHS.varType.primitiveType == NUM){
                        return INT_DT;
                    }
                    else{
                        printf("Type Error: expecting INTEGER");
                    }
                }
            }
            else if (current->leftChild->name.t.tid == ID && current->leftChild->rightSibling->name.t.tid == ID){
                entryDataType locationTypeRHS = searchSymbolTable(current->leftChild->rightSibling->pt->element.t.lexeme, table)->entry_DT;
                entryDataType locationTypeLHS = searchSymbolTable(current->leftChild->pt->element.t.lexeme, table)->entry_DT;
                if(locationTypeRHS.isArray == 1 || locationTypeLHS.isArray == 1){
                    printf("Type Error: expecting INTEGER, recieved array");
                }
                else if (locationTypeRHS.isArray == 0 && locationTypeLHS.isArray == 0){
                    if(locationTypeLHS.varType.primitiveType == NUM && locationTypeRHS.varType.primitiveType == NUM){
                        return INT_DT;
                    }
                    else{
                        printf("Type Error: expecting INTEGER");
                    }
                }
            }
            else{
                printf("Type Error: expecting INTEGER");
            }
            break;
        case 0:
            break;
        case 18:

            break;
            
        default:
            break;
        }
    }
    else{
        switch (current->name.t.tid)
        {
        case 2:
            dType termType;
            astNode* temp = current->leftChild;
            if(temp->name.t.tid == ID){
                termType = staticTypeChecking(temp, table);
            }
            while(temp->rightSibling->name.t.tid != EPSILON){

            }
            break;
        
        default:
            break;
        }

    }
}