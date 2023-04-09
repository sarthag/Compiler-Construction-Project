#include "codeGen.h"


void generateASMCode(FILE* asmFile){
    if(asmFile == NULL){
        printf("File is Invalid");
    }

    for(int i=0;i<MAXLINES;i++){
        switch(intermediateCode[i].label){
            case INT_ADD:
                //addition of integer variable 
                readWriteST(1, 2, intermediateCode[i].op1, asmFile);
                fprintf(asmFile,"\tMOV AX, BX\n");
                readWriteST(1, 2, intermediateCode[i].op2, asmFile);
                fprintf(asmFile,"\tADD AX, BX\n");
                fprintf(asmFile, "\tMOV BX, AX\n");
                readWriteST(0, 2, intermediateCode[i].lhs, asmFile);
                break;

            case INT_SUB:
                //subtraction of integer variable 
                readWriteST(1, 2, intermediateCode[i].op1, asmFile);
                fprintf(asmFile,"\tMOV AX, BX\n");
                readWriteST(1, 2, intermediateCode[i].op2, asmFile);
                fprintf(asmFile,"\tSUB AX, BX\n");
                fprintf(asmFile, "\tMOV BX, AX\n");
                readWriteST(0, 2, intermediateCode[i].lhs, asmFile);
                break;

            case INT_MUL:
                //Mul of integer variable 
                readWriteST(1, 2, intermediateCode[i].op1, asmFile);
                fprintf(asmFile,"\tMOV AX, BX\n");
                readWriteST(1, 2, intermediateCode[i].op2, asmFile);
                fprintf(asmFile,"\tMUL AX, BX\n");
                fprintf(asmFile, "\tMOV BX, AX\n");
                readWriteST(0, 2, intermediateCode[i].lhs, asmFile);
                break;

            //look into this case 
            case INT_DIV:
                //division of integer variable 
                readWriteST(1, 2, intermediateCode[i].op1, asmFile);
                fprintf(asmFile,"\tMOV AX, BX\n");
                readWriteST(1, 2, intermediateCode[i].op2, asmFile);
                fprintf(asmFile,"\tDIV AX, BX\n");
                fprintf(asmFile, "\tMOV BX, AX\n");
                readWriteST(0, 2, intermediateCode[i].lhs, asmFile);
                break;

            default:
        }
    }
}

void readWriteST(bool isRead, int width, symbolRecord* rec, FILE* asmFile){
    char b[8];
    switch (width)
    {
    case 1:
        sprintf(b, "BL");
        break;
    case 2:
        sprintf(b, "BX");
        break;
    case 4:
        sprintf(b, "EBX");
        break;
    default:
        sprintf(b, "RBX");
        break;
    }

    if(rec->parentTable==globalTable){
        fprintf(asmFile, "\tPUSH EBP\n");
        fprintf(asmFile, "\tMOV EBP, %d\n", globalTable->baseOffset);
    }
    //EBP holds the base address of the symbol table 

    if(isRead==0){
        //writing into symbol table record 
        fprintf("\tMOV %s, [EBP+%d]\n",b,rec->offset);
    }
    else if(isRead==1){
        //reading from the symbol table 
        fprintf("\tMOV [EBP+%d], %s\n",rec->offset, b);
    }

    if(rec->parentTable==globalTable){
        fprintf(asmFile, "\tPOP EBP\n");
    }
}

