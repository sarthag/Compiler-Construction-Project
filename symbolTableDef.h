#ifndef SYMBOLTABLEDEF_H
#define SYMBOLTABLEDEF_H

#include "ast.h"

#define ST_SIZE 300
/*
Figure out what alias is 
single table or divide it into 3-4 tables 
*/


typedef enum{
    INT_DT, REAL_DT, BOOL_DT, NA
}dType;

typedef enum{
    VARIABLE, FUNCTION, CONDITIONAL, ITERATIVE
}stEntryType;

typedef struct usageLLNode{
    int line_no;
    int scope; //global scope is definded as 0 and each subsequent scope has an integer associated to it  
    struct usageLLNode* next; 
    struct usageLLNode* prev;     
} usageLLNode;


typedef struct usageLL{
    struct usageLLNode* head; 
    struct usageLLNode* tail; 
    int count; 
} usageLL; 

typedef struct arrayType{
    dType arraydType;
    int lowerBound;
    int upperBound;
}arrayType;

typedef struct symbolRecord{
    char* name; 

    bool isScope;  //isScope is 1 if it is a function, conditional or iterative stmt 
    struct symbolTable* scopePointer; //if isScope = 1 then points to the symbol table of the next scope 
    stEntryType entryType; //for storing whether it is a variable function conditional or iterative stmt
    struct symbolTable* parentTable;  
    struct symbolRecord* nextEntry;
    bool isArray;
    union{
        dType primitiveType;
        arrayType arr;
    }varType;
     
    int size;
    int offset;
    bool occupied; //to see if this symbolrecord is occupied or not helps in hashing
    // int dimension
    // int line_of_declaration; 
    //usageLL line_of_usage; //if the linked list approach is going to be used 
    // astNode* address; 
} symbolRecord;

typedef struct symbolTable{
    char *tableName; //function name / iterative stmts name / conditional stmts name 

    int baseOffset;
    int tableWidth;
    struct symbolTable* parentTable; //table to return to 
    struct symbolTable* nextTable; //not sure if this is needed since there are no nested functions 
    symbolRecord symbTable[ST_SIZE]; // Temp delete if wrong 
    //symbolRecord* firstEntry; 
    //symbolRecord* lastEntry; 
    //array of enteries 
}symbolTable;


symbolTable* globalTable;
int counter = 0;
char counterStr[20];


#endif