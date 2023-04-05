#ifndef SYMBOLTABLEDEF_H
#define SYMBOLTABLEDEF_H

#include "astadt.h"

typedef enum dataType{
    INTEGER, REAL, BOOLEAN, ARRAY
}dataType;

typedef struct symbolRecord{
    char* name; 
    dataType type; 
    int size;
    int line_of_declaration; 
    usageLL line_of_usage; 
} record;



#endif