#include "symbolTable.h"

/*
 Terminals for type-checking: ASSIGNOP, PLUS, MINUS, MUL, DIV, LE, GE, LT, GT, EQ, NE, AND, OR, (ARRAYS for each op)
*/

dType staticTypeChecking(astNode * current, symbolTable * table);

dType checkBool(astNode * current, symbolTable * table){
    dType boolType;
    astNode* temp = current->leftChild;
    if(temp->name.t.tid == ID){
        symbolRecord* record = searchAllSymbolTable(temp->pt->element.t.lexeme, table);
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
            if(record->entry_DT.isArray == 0){
                if (boolType == record->entry_DT.varType.primitiveType){
                    continue;
                }
                else{
                    printf("Type Error");
                    return -1;
                }
            }
            else{
                if (boolType == record->entry_DT.varType.arr.arraydType){
                    continue;
                }
                else{
                    printf("Type Error");
                    return -1;
                }
            }
        }
        else if(temp->leftChild->nodeType == NON_TERMINAL){
            if (boolType == staticTypeChecking(temp->leftChild, table)){
                continue;
            }
            else{
                printf("Type Error");
                return -1;
            }
        }
        else{
            if (boolType == gettypeFromtid(temp->leftChild, table).varType.primitiveType){
                continue;
            }
            else{
                printf("Type Error");
                return -1;
            }
        }
    }
    return BOOL_DT;
}

dType staticTypeChecking(astNode * current, symbolTable * table){
    if(current->nodeType == TERMINAL){
        switch (current->name.t.tid)
        {
        case 1:
            return checkBool(current, table);
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
                                return -1;
                            }
                        }
                    }
                    else if (current->leftChild->rightSibling->name.t.tid == NUM){
                        if (locationTypeLHS.varType.primitiveType == INT_DT){
                            return INT_DT;
                        }
                        else{
                            printf("type mismatch");
                            return -1;
                        }
                    }
                    else if (current->leftChild->rightSibling->name.t.tid == RNUM){
                        if (locationTypeLHS.varType.primitiveType == REAL_DT){
                            return REAL_DT;
                        }
                        else{
                            printf("type mismatch");
                            return -1;
                        }
                    }
                    else if (locationTypeLHS.varType.primitiveType == staticTypeChecking(current->leftChild->rightSibling, table)){
                        return locationTypeLHS.varType.primitiveType;
                    }
                    else{
                        printf("type mismatch");
                        return -1;
                    }
                }
                else if(locationTypeLHS.isArray == 1){
                    if(locationTypeLHS.varType.arr.arraydType != INT_DT){
                        printf("Expected Integer as index");
                        return -1;
                    }
                    if(locationTypeLHS.varType.arr.lowerBound.bound < current->leftChild->leftChild->pt->element.t.num && locationTypeLHS.varType.arr.upperBound.bound > current->leftChild->leftChild->pt->element.t.num){
                        dType arrType = locationTypeLHS.varType.arr.arraydType;
                        if(current->leftChild->rightSibling->name.t.tid == ID){
                            entryDataType locationTypeRHS = searchAllSymbolTable(current->leftChild->rightSibling->pt->element.t.lexeme, table)->entry_DT;
                            if(locationTypeRHS.isArray == 0){
                                if(arrType == locationTypeRHS.varType.primitiveType){
                                    return locationTypeLHS.varType.primitiveType;
                                }
                                else{
                                    printf("type mismatch");
                                    return -1;
                                }
                            }
                        }
                        else if (current->leftChild->rightSibling->name.t.tid == NUM){
                            if (arrType == INT_DT){
                                return INT_DT;
                            }
                            else{
                                printf("type mismatch");
                                return -1;
                            }
                        }
                        else if (current->leftChild->rightSibling->name.t.tid == RNUM){
                            if (arrType == REAL_DT){
                                return REAL_DT;
                            }
                            else{
                                printf("type mismatch");
                                return -1;
                            }
                        }
                        else if (arrType == staticTypeChecking(current->leftChild->rightSibling, table)){
                            return locationTypeLHS.varType.primitiveType;
                        }
                        else{
                            printf("type mismatch");
                            return -1;
                        }
                    }
                    else{
                        printf("Array index out of bound");
                        return -1;
                    }
                }
            }
            else{
                printf("assigning to  non-variable entity");
                return -1;
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
                    return -1;                   
                }
                else if (locationTypeLHS.isArray == 0){
                    if(locationTypeLHS.varType.primitiveType == INT_DT){
                        return INT_DT;
                    }
                    else{
                        printf("Type Error: expecting INTEGER");
                        return -1;
                    }
                }
            }
            else if (current->leftChild->name.t.tid == NUM && current->leftChild->rightSibling->name.t.tid == ID){
                entryDataType locationTypeRHS = searchSymbolTable(current->leftChild->rightSibling->pt->element.t.lexeme, table)->entry_DT;
                if(locationTypeRHS.isArray == 1){
                    printf("Type Error: expecting INTEGER, recieved array");
                    return -1;
                }
                else if (locationTypeRHS.isArray == 0){
                    if(locationTypeRHS.varType.primitiveType == NUM){
                        return INT_DT;
                    }
                    else{
                        printf("Type Error: expecting INTEGER");
                        return -1;
                    }
                }
            }
            else if (current->leftChild->name.t.tid == ID && current->leftChild->rightSibling->name.t.tid == ID){
                entryDataType locationTypeRHS = searchAllSymbolTable(current->leftChild->rightSibling->pt->element.t.lexeme, table)->entry_DT;
                entryDataType locationTypeLHS = searchAllSymbolTable(current->leftChild->pt->element.t.lexeme, table)->entry_DT;
                if(locationTypeRHS.isArray == 1 || locationTypeLHS.isArray == 1){
                    printf("Type Error: expecting INTEGER, recieved array");
                    return -1;
                }
                else if (locationTypeRHS.isArray == 0 && locationTypeLHS.isArray == 0){
                    if(locationTypeLHS.varType.primitiveType == NUM && locationTypeRHS.varType.primitiveType == NUM){
                        return INT_DT;
                    }
                    else{
                        printf("Type Error: expecting INTEGER");
                        return -1;
                    }
                }
            }
            else{
                printf("Type Error: expecting INTEGER");
                return -1;
            }
            break;
        case 15:
            return checkBool(current, table);
        case 18:
            return checkBool(current, table);
        case 19:
            return checkBool(current, table);
        case 21:
            return checkBool(current, table);
        case 22:
            return checkBool(current, table);    
        default:
            break;
        }
    }
    else{
        dType termType, factorPrimType;
        astNode* temp = current->leftChild;
        switch (current->name.nt.nid)
        {
        case 2:
            //dType termType;
            //astNode* temp = current->leftChild;
            if(temp->name.t.tid == ID){
                symbolRecord* record = searchAllSymbolTable(temp->pt->element.t.lexeme, table);
                if(record->entry_DT.isArray == 0){
                    termType = record->entry_DT.varType.primitiveType;
                }
                else{
                    termType = record->entry_DT.varType.arr.arraydType;
                }
            }
            else if(temp->nodeType == NON_TERMINAL){
                termType = staticTypeChecking(temp->leftChild, table);
            }
            else{
                termType = gettypeFromtid(temp, table).varType.primitiveType;
            }
            while(temp->rightSibling->name.t.tid != EPSILON){
                temp = temp->rightSibling;
                if(temp->leftChild->name.t.tid == ID){
                    symbolRecord* record = searchAllSymbolTable(temp->pt->element.t.lexeme, table);
                    if(record->entry_DT.isArray == 0){
                        if (termType == record->entry_DT.varType.primitiveType){
                            continue;
                        }
                        else{
                            printf("Type Error");
                            return -1;
                        }
                    }
                    else{
                        if (termType == record->entry_DT.varType.arr.arraydType){
                            continue;
                        }
                        else{
                            printf("Type Error");
                            return -1;
                        }
                    }
                }
                else if(temp->leftChild->nodeType == NON_TERMINAL){
                    if (termType == staticTypeChecking(temp->leftChild, table)){
                        continue;
                    }
                    else{
                        printf("Type Error");
                        return -1;
                    }
                }
                else{
                    if (termType == gettypeFromtid(temp->leftChild, table).varType.primitiveType){
                        continue;
                    }
                    else{
                        printf("Type Error");
                        return -1;
                    }
                }
            }
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
                        if(record->entry_DT.isArray == 0){
                            if (factorPrimType == record->entry_DT.varType.primitiveType){
                                continue;
                            }
                            else{
                                printf("Type Error");
                                return -1;
                            }
                        }
                        else{
                            if (factorPrimType == record->entry_DT.varType.arr.arraydType){
                                continue;
                            }
                            else{
                                printf("Type Error");
                                return -1;
                            }
                        }
                    }
                    else if(temp->leftChild->nodeType == NON_TERMINAL){
                        if (factorPrimType == staticTypeChecking(temp->leftChild, table)){
                            continue;
                        }
                        else{
                            printf("Type Error");
                            return -1;
                        }
                    }
                    else{
                        if (factorPrimType == gettypeFromtid(temp->leftChild, table).varType.primitiveType){
                            continue;
                        }
                        else{
                            printf("Type Error");
                            return -1;
                        }
                    }
                }
                else if (temp->name.t.tid == DIV){
                    factorPrimType = REAL_DT;
                }
            }
            return factorPrimType;
        default:
            return -1;
            break;
        }

    }
}