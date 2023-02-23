//All data definitions used in lexer.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 65535

typedef struct twinBuffer{
    char buffer1[BUFFERSIZE+1];
    char buffer2[BUFFERSIZE+1];
}twinBuffer;

