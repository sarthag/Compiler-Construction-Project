#include "symbolTable.h"


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