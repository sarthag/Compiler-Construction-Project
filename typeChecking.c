#include "symbolTable.h"

void staticTypeChecking(astNode * current, symbolTable * table){
    if(current->nodeType == TERMINAL){
        switch (current->name.t.tid)
        {
        case 10:
            if(current->leftChild->name.t.tid == ID){
                entryDataType locationType = searchSymbolTable(current->leftChild->pt->element.t.lexeme, table)->entry_DT;
                if(locationType.isArray != 1){
                    if(current->leftChild->rightSibling->name.t.tid == ID){
                        if(locationType.varType.primitiveType == gettypeFromtid(current->leftChild->rightSibling, globalTable).varType.primitiveType){
                            return gettypeFromtid(current->leftChild, globalTable).varType.primitiveType;
                        }
                        else{
                            printf("type mismatch");
                            return;
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
        
        default:
            break;
        }
    }
}
