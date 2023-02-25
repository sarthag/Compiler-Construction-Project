#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <lexerDef.h>

#define PRIME 997
#define KTSIZE 103
#define MOD 1e9+7
typedef struct ktElement{
    char *lexeme;
    token_key  token;
    bool occupied;
}ktElement;

ktElement keywordTable[KTSIZE];

