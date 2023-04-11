#include "symbolTable.h"

/*
1) ** The types and the number of parameters returned by a function must be the same as that of the parameters used in 
invoking the function. 
2) ** The parameters being returned by a function must be assigned a value. 
If a parameter does not get a value assigned within the function definition, it should be reported as an error. 
3) The function that does not return any value, must be invoked appropriately. 
4) ** Function input parameters passed while invoking it should be of the same type as those used in the function definition.

difficult : 
5) A function declaration for a function being used (say F1) by another (say F2) must precede the definition of the 
function using it(i.e. F2), only if the function definition of F1 does not precede the definition of F2. 
6) If the function definition of F1 precedes function definition of F2(the one which uses F1), then the function 
declaration of F1 is redundant and is not valid. 

Function overloading is not allowed. //taken care in the symbol table itself
The function cannot be invoked recursively. //taken care by grammar rules 
*/

//during function CALL- Function INPUT parameters passed while invoking it should be of the same type as those used in the 
//function definition
void matchInputParams(char* funcName, astNode* inputParams){
    symbolRecord* funcGlobalEntry= searchSymbolTable(funcName, globalTable);
    astNode* actualParaList = inputParams;
    struct plistNode* temp = funcGlobalEntry->input_plist.head;
    while(temp != NULL){
        entryDataType edt= gettypeFromtid(actualParaList, funcGlobalEntry->scopePointer);

        actualParaList= actualParaList->rightSibling;
        temp = temp->next;

        if(temp->entryDT.isArray != edt.isArray){
            printf("ERROR: Mismatch between array and non-array element\n");
        }
        if(temp->entryDT.isArray==false){
            //not array elements 
            if(temp->entryDT.varType.primitiveType != edt.varType.primitiveType){
                printf("ERROR: Datatype Mismatch in Input Paramaters (Primitive case)");
            }
        }
        else{
            //array elements
            if(temp->entryDT.varType.arr.arraydType != edt.varType.arr.arraydType){
                printf("ERROR: Datatype Mismatch in Input Paramaters (Array case) ");
            } 
        }
        //check if there is a mismatch in the number of parameters
        if(temp ==NULL && actualParaList !=NULL || temp !=NULL && actualParaList ==NULL){
            printf("ERROR: Mismatch between number of elements returned and function invokation \n");
        }
    }
    
}


//during function DEFINITION - the return parameters are matched to the parameters of function invokation
//invoke params -> idList1
void matchReturnParams(astNode* assignParams, char* funcName){
    symbolRecord* func = searchSymbolTable(funcName, globalTable);
    astNode* idListTemp = assignParams;
    struct plistNode* temp = func->output_plist.head;
    if(func->isFuncDef == true){
            while(temp != NULL){
                entryDataType edt= gettypeFromtid(idListTemp, func->scopePointer);
                if(temp->entryDT.varType.primitiveType != edt.varType.primitiveType){
                    printf("ERROR: Datatype Mismatch in return parameters \n");
                }
                
                temp = temp -> next;
                idListTemp = idListTemp->rightSibling;

                if(temp ==NULL && idListTemp !=NULL || temp !=NULL && idListTemp ==NULL){
                    printf("ERROR: Mismatch between number of elements returned and function invokation \n");
                }
            }
    }
}

void checkNestedFunctionCall(symbolTable* funcST) {
    for(int i=0; i<ST_SIZE;i++){
        if(funcST->symbTable[i]->isScope==true && funcST->symbTable[i]->entryType==FUNCTION){
            //this is a nested function 
            
        }
    }
}

