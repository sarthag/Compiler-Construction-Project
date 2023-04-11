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

typedef union{
    int bound;
    char* variable;
}boundType;

typedef struct arrayType{
    dType arraydType;
    bool isDynamic;   // ADD CODE FOR THIS
    boundType lowerBound;
    boundType upperBound;
}arrayType;

typedef union{
    dType primitiveType;
    arrayType arr;
}vartype;

typedef struct{
    bool isArray;
    vartype varType;
}entryDataType;

typedef struct plistNode{
    char* name; 
    entryDataType entryDT; 
    struct plistNode* next;
}plistNode; 

typedef struct plist{
    int numParams; 
    struct plistNode* head; 
    struct plistNode* tail; 
}plist; 

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
    bool isFuncDef;
    bool funcCall;
    struct plist input_plist; 
    struct plist output_plist;     
} symbolRecord;

typedef struct symbolTable{
    char *tableName; //function name / iterative stmts name / conditional stmts name 
    int latestOffset;
    int tableWidth;
    int nestingLevel; 
    struct symbolTable* parentTable; //table to return to  
    symbolRecord* symbTable[ST_SIZE];
    struct symbolTable* tempTable;
    int scopeBeginLine;
    int scopeEndLine;
    
}symbolTable;


symbolTable* globalTable;
int counter = 0;
char counterStr[20];


#endif