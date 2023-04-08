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
                symbolRecord* rightOp = findFromST(node ->leftChild -> rightSibling->name.t.lexeme,table);
                if(leftOp->varType.primitiveType == INT_DT && rightOp->varType.primitiveType == INT_DT){
                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table,INT_DT);
                    intermediateCode[icgLineNo].op1 = leftOp;
                    intermediateCode[icgLineNo].op2 = rightOp;
                    intermediateCode[icgLineNo].label = INT_ADD;
                    icgLineNo++;

                }

                else if(leftOp->varType.primitiveType == REAL_DT && rightOp->varType.primitiveType == REAL_DT){
                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = leftOp;
                    intermediateCode[icgLineNo].op2 = rightOp;
                    intermediateCode[icgLineNo].label = REAL_ADD;
                    icgLineNo++;
                }

                else if(leftOp->varType.primitiveType == INT_DT && rightOp->varType.primitiveType == REAL_DT){
                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = leftOp;
                    intermediateCode[icgLineNo].label = INT_TO_REAL;
                    icgLineNo++;

                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = intermediateCode[icgLineNo-1].lhs;
                    intermediateCode[icgLineNo].op2 = rightOp;
                    intermediateCode[icgLineNo].label = REAL_ADD;
                    icgLineNo++;
                }

                else if(leftOp->varType.primitiveType == REAL_DT && rightOp->varType.primitiveType == INT_DT){
                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = rightOp;
                    intermediateCode[icgLineNo].label = INT_TO_REAL;
                    icgLineNo++;

                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = leftOp;
                    intermediateCode[icgLineNo].op2 = intermediateCode[icgLineNo-1].lhs;
                    intermediateCode[icgLineNo].label = REAL_ADD;
                    icgLineNo++;
                }

            case MINUS:
                // symbolRecord* tempVar;
                createICG(node -> leftChild, table);
                createICG(node -> leftChild -> rightSibling, table);
                symbolRecord* leftOp = findFromST(node ->leftChild->name.t.lexeme,table);
                symbolRecord* rightOp = findFromST(node ->leftChild -> rightSibling->name.t.lexeme,table);
                if(leftOp->varType.primitiveType == INT_DT && rightOp->varType.primitiveType == INT_DT){
                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table,INT_DT);
                    intermediateCode[icgLineNo].op1 = leftOp;
                    intermediateCode[icgLineNo].op2 = rightOp;
                    intermediateCode[icgLineNo].label = INT_SUB;
                    icgLineNo++;

                }

                else if(leftOp->varType.primitiveType == REAL_DT && rightOp->varType.primitiveType == REAL_DT){
                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = leftOp;
                    intermediateCode[icgLineNo].op2 = rightOp;
                    intermediateCode[icgLineNo].label = REAL_SUB;
                    icgLineNo++;
                }

                else if(leftOp->varType.primitiveType == INT_DT && rightOp->varType.primitiveType == REAL_DT){
                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = leftOp;
                    intermediateCode[icgLineNo].label = INT_TO_REAL;
                    icgLineNo++;

                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = intermediateCode[icgLineNo-1].lhs;
                    intermediateCode[icgLineNo].op2 = rightOp;
                    intermediateCode[icgLineNo].label = REAL_SUB;
                    icgLineNo++;
                }

                else if(leftOp->varType.primitiveType == REAL_DT && rightOp->varType.primitiveType == INT_DT){
                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = rightOp;
                    intermediateCode[icgLineNo].label = INT_TO_REAL;
                    icgLineNo++;

                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = leftOp;
                    intermediateCode[icgLineNo].op2 = intermediateCode[icgLineNo-1].lhs;
                    intermediateCode[icgLineNo].label = REAL_SUB;
                    icgLineNo++;
                }

            case MUL:
                // symbolRecord* tempVar;
                createICG(node -> leftChild, table);
                createICG(node -> leftChild -> rightSibling, table);
                symbolRecord* leftOp = findFromST(node ->leftChild->name.t.lexeme,table);
                symbolRecord* rightOp = findFromST(node ->leftChild -> rightSibling->name.t.lexeme,table);
                if(leftOp->varType.primitiveType == INT_DT && rightOp->varType.primitiveType == INT_DT){
                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table,INT_DT);
                    intermediateCode[icgLineNo].op1 = leftOp;
                    intermediateCode[icgLineNo].op2 = rightOp;
                    intermediateCode[icgLineNo].label = INT_MUL;
                    icgLineNo++;

                }

                else if(leftOp->varType.primitiveType == REAL_DT && rightOp->varType.primitiveType == REAL_DT){
                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = leftOp;
                    intermediateCode[icgLineNo].op2 = rightOp;
                    intermediateCode[icgLineNo].label = REAL_MUL;
                    icgLineNo++;
                }

                else if(leftOp->varType.primitiveType == INT_DT && rightOp->varType.primitiveType == REAL_DT){
                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = leftOp;
                    intermediateCode[icgLineNo].label = INT_TO_REAL;
                    icgLineNo++;

                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = intermediateCode[icgLineNo-1].lhs;
                    intermediateCode[icgLineNo].op2 = rightOp;
                    intermediateCode[icgLineNo].label = REAL_MUL;
                    icgLineNo++;
                }

                else if(leftOp->varType.primitiveType == REAL_DT && rightOp->varType.primitiveType == INT_DT){
                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = rightOp;
                    intermediateCode[icgLineNo].label = INT_TO_REAL;
                    icgLineNo++;

                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = leftOp;
                    intermediateCode[icgLineNo].op2 = intermediateCode[icgLineNo-1].lhs;
                    intermediateCode[icgLineNo].label = REAL_MUL;
                    icgLineNo++;
                }

            case DIV:
                // symbolRecord* tempVar;
                createICG(node -> leftChild, table);
                createICG(node -> leftChild -> rightSibling, table);
                symbolRecord* leftOp = findFromST(node ->leftChild->name.t.lexeme,table);
                symbolRecord* rightOp = findFromST(node ->leftChild -> rightSibling->name.t.lexeme,table);
                if(leftOp->varType.primitiveType == INT_DT && rightOp->varType.primitiveType == INT_DT){
                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table,INT_DT);
                    intermediateCode[icgLineNo].op1 = leftOp;
                    intermediateCode[icgLineNo].op2 = rightOp;
                    intermediateCode[icgLineNo].label = INT_DIV;
                    icgLineNo++;

                }

                else if(leftOp->varType.primitiveType == REAL_DT && rightOp->varType.primitiveType == REAL_DT){
                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = leftOp;
                    intermediateCode[icgLineNo].op2 = rightOp;
                    intermediateCode[icgLineNo].label = REAL_DIV;
                    icgLineNo++;
                }

                else if(leftOp->varType.primitiveType == INT_DT && rightOp->varType.primitiveType == REAL_DT){
                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = leftOp;
                    intermediateCode[icgLineNo].label = INT_TO_REAL;
                    icgLineNo++;

                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = intermediateCode[icgLineNo-1].lhs;
                    intermediateCode[icgLineNo].op2 = rightOp;
                    intermediateCode[icgLineNo].label = REAL_DIV;
                    icgLineNo++;
                }

                else if(leftOp->varType.primitiveType == REAL_DT && rightOp->varType.primitiveType == INT_DT){
                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = rightOp;
                    intermediateCode[icgLineNo].label = INT_TO_REAL;
                    icgLineNo++;

                    intermediateCode[icgLineNo].lhs = insertIntoTempTable(table, REAL_DT);
                    intermediateCode[icgLineNo].op1 = leftOp;
                    intermediateCode[icgLineNo].op2 = intermediateCode[icgLineNo-1].lhs;
                    intermediateCode[icgLineNo].label = REAL_DIV;
                    icgLineNo++;
                }
        }
    }


}

void generateIC(){
    tempVarCounter = 0;
    icgLineNo = 0;
    
}