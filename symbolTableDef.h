#ifndef SYMBOLTABLEDEF_H
#define SYMBOLTABLEDEF_H

#include "ast.h"

#define ST_SIZE 300
#define INT_WIDTH 2
#define REAL_WIDTH 4
#define BOOL_WIDTH 1
#define ARRAY_WIDTH_EXTRA 1


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

typedef union{
    dType primitiveType;
    arrayType arr;
}vartype;

typedef struct{
    bool isArray;
    vartype varType;
}entryDataType;

typedef struct symbolRecord{
    char* name; 
    bool isScope;  //isScope is 1 if it is a function, conditional or iterative stmt 
    struct symbolTable* scopePointer; //if isScope = 1 then points to the symbol table of the next scope 
    stEntryType entryType; //for storing whether it is a variable function conditional or iterative stmt
    struct symbolTable* parentTable;  
    struct symbolRecord* nextEntry;
    entryDataType entry_DT; 
    int width;
    int offset;
    bool occupied; //to see if this symbolrecord is occupied or not helps in hashing 

    bool isFuncDeclaration;
    bool funcCall;
} symbolRecord;

typedef struct symbolTable{
    char *tableName; //function name / iterative stmts name / conditional stmts name 
    int latestOffset;
    int tableWidth;
    int nestingLevel; 
    struct symbolTable* parentTable; //table to return to 
    // struct symbolTable* nextTable; //not sure if this is needed since there are no nested functions 
    symbolRecord* symbTable[ST_SIZE]; // Temp delete if wrong 
    struct symbolTable* tempTable;
    
}symbolTable;


symbolTable* globalTable;
int counter = 0;
char counterStr[20];
entryDataType na;


#endif