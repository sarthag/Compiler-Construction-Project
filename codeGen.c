#include "codeGen.h"

//generate temporary variable
//generate labels
//find the next offset 

void generateAssembly(FILE* asmFile, astNode* node){
    if(node==NULL){
        return ;
    }
    if(node->pt->element.nt.nid== program){
        //data section definitions
        fprintf(asmFile, "section .data\n");

        fprintf(asmFile, "section .text\n");
        fprintf(asmFile, "default rel\n");
        fprintf(asmFile, "extern printf\n");
        fprintf(asmFile, "extern scanf\n");
        fprintf(asmFile, "global main\n");

        //call the children of program 
        astNode* temp = node->leftChild;
        while(temp!=NULL){
            generateAssembly(asmFile, temp);
            temp = temp->rightSibling;
        }
    }

    else if(node->pt->element.nt.nid == otherModules){
        //recursively call the children
        astNode* temp = node->leftChild;
        while(temp!=NULL){
            generateAssembly(asmFile, temp);
            temp = temp->rightSibling;
        }
    }

    else if(node->pt->element.nt.nid == driverModule){

    }
}
