#ifndef SYMBOLTABLEDEF_H
#define SYMBOLTABLEDEF_H

#include "astadt.h"

/*
Figure out what alias is 
single table or divide it into 3-4 tables 
*/


typedef enum dataType{
    INT_DT, REAL_DT, BOOL_DT, ARRAY_DT
}dataType;

typedef struct usageLLNode{
    int line_no;
    int scope; //global scope is definded as 0 and each subsequent scope has an integer associated to it  
    usageLLNode* next; 
    usageLLNode* prev;     
} usageLLNode;


typedef struct usageLL{
    usageLLNode* head; 
    usageLLNode* tail; 
    int count; 
} usageLL; 


typedef struct symbolRecord{
    char* name; 
    dataType type; 
    int size;
    // int offset; 
    // int dimension
    // int line_of_declaration; 
    usageLL line_of_usage;
    astNode* address; 
} record;

record symbtTable[200]; // Temp delete if wrong 

#endif