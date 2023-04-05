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


typedef struct symbolTable{

} symbolTable;

typedef struct symbolRecord{
    char* name; 

    bool isScope;  //isScope is 1 if it is a function, conditional or iterative stmt 
    symbolTable* scopePointer; //if isScope = 1 then points to the symbol table of the next scope 

    symbolTable* parentTable;  
    symbolRecord* nextEntry;

    dataType type; 
    int size;
    int offset; 
    // int dimension
    // int line_of_declaration; 
    usageLL line_of_usage; //if the linked list approach is going to be used 
    // astNode* address; 
} symbolRecord;

typedef struct symnolTable{
    char *tableName; //function name / iterative stmts name / conditional stmts name 
    int baseOffset;
    int tableWidth;
    symbolTable* parentTable; //table to return to 
    symbolTable* nextTable; //not sure if this is needed since there are no nested functions 

    symbolRecord* firstEntry; 
    //array of enteries 
}symbolTable;

//symbolRecord symbtTable[200]; // Temp delete if wrong 

#endif