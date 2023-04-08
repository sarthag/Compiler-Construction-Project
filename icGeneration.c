#include "icGeneration.h"

symbolRecord* insertIntoTempTable(symbolTable * parentTable, dType tempType){
    symbolRecord* new;
    if(parentTable->tempTable==NULL){
        parentTable ->tempTable = createSymbolTable("temp",parentTable);
    }
    char* tempVarName = (char*)malloc(100*sizeof(char));
    sprintf(tempVarName,"temp_%d",tempVarCounter++);
    
    return new = insertIntoSymbolTable(parentTable -> tempTable,tempVarName,VARIABLE,tempType);

}

symbolRecord* findFromST(char* recordName, symbolTable* table){
    symbolRecord* entry;
    entry = searchSymbolTable(recordName,table);
    if(entry == NULL){
        entry = searchSymbolTable(recordName, table ->tempTable);
    }
    
}

void createICG(astNode* node, symbolTable* table){
    //keep track of which table we are in depending on ast 
    if(node == NULL){
        printf("ERROR: AST IS EMPTY");
    }
    if(node ->nodeType == TERMINAL){
        switch(node ->name.t.tid){
            case PLUS :
                // symbolRecord* tempVar;
                createICG(node -> leftChild, table);
                createICG(node -> leftChild -> rightSibling, table);
                symbolRecord* leftOp = findFromST(node ->leftChild->name.t.lexeme,table);
                symbolRecord* rightOp = sfindFromST(node ->leftChild -> rightSibling->name.t.lexeme,table);
                if(leftOp->varType.primitiveType == INT_DT && leftOp->varType.primitiveType == INT_DT){
                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table,INT_DT);
                    intermediateCode[icgLineNo].op1 = leftOp;
                    intermediateCode[icgLineNo].op2 = rightOp;
                    intermediateCode[icgLineNo].label = INT_ADD;

                }

                
            
        }
    }


}

void generateIC(){
    tempVarCounter = 0;
    icgLineNo = 0;
    
}