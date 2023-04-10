#include "symbolTable.h"

void staticTypeChecking(astNode * current){
    if(current->nodeType == TERMINAL){
        switch (current->name.t.tid)
        {
        case 10:
            if(current->leftChild->nodeType == TERMINAL){
                if(current->leftChild->rightSibling == TERMINAL){
                    if(gettypeFromtid(current->leftChild, globalTable).varType.primitiveType == gettypeFromtid(current->leftChild->rightSibling, globalTable).varType.primitiveType){
                        return gettypeFromtid(current->leftChild, globalTable).varType.primitiveType;
                    }
                    else{
                        printf("type mismatch");
                        return;
                    }
                }
                else{
                    
                }
            }
            break;
        
        default:
            break;
        }
    }
}
