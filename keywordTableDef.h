#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PRIME 997
#define KTSIZE 103
#define MOD 1e9+7
typedef struct ktElement{
    char *lexeme;
    int  token;
    bool occupied;
}ktElement;

ktElement keywordTable[KTSIZE];

