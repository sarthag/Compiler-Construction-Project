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

//during function call
void matchReturnParams(char* funcName, astNode* assignParams){
    //return parameters are obtained from function defention and assignParams from function call
    symbolRecord* funcGlobalEntry= searchSymbolTable(funcName, globalTable);
    //match the output type linked list to the assignParams linked list 
}


//the parameters passed while invoking should be the same as those during function defenition
void matchInputParams(astNode* invokeParams, char* funcName){
    symbolRecord* func = searchSymbolTable(funcName, globalTable);
    if(func->isFuncDeclaration == true){
        /*
            temp = func->linkedListHead;
            while(temp != NULL){
                if(temp.type != invokeParams.type){
                    printf("ERROR: The function invocation doesn't match the function declaration");
                }
                temp = temp -> next;
            }
        */
    }
}

void checkNestedFunctions(symbolTable* funcST) {
    for(int i=0; i<ST_SIZE;i++){
        if(funcST->symbTable[i]->isScope==true && funcST->symbTable[i]->entryType==FUNCTION){
            //this is a nested function 
            
        }
    }
}

