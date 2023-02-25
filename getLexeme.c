#include "lexer.h"
#include "lexer.h"
#include "lexerDef.h"

char *getLexeme() {
    char *lex = (char *) malloc((numChar + 1) * sizeof(char));
    int c = 0;
    char *curr = begin;
    bool case_1 = begin >= buffers.buffer1 && begin <= buffers.buffer1 + BUFFERSIZE;
    bool case_2 = forward >= buffers.buffer1 && forward <= buffers.buffer1 + BUFFERSIZE;
    bool case_3 = begin >= buffers.buffer2 && begin <= buffers.buffer2 + BUFFERSIZE;
    bool case_4 = forward >= buffers.buffer1 && forward <= buffers.buffer1 + BUFFERSIZE;

    if((case_1 && case_2) || (case_3 && case_4)) {
        while(curr < forward) {
            lex[c] = *curr;
            c++;
            curr++;
        }
    }
    else if(case_1 && case_4) {
        while(curr < buffers.buffer1 + BUFFERSIZE) {
            lex[c] = *curr;
            c++;
            curr++;
        }
        curr = buffers.buffer2;
        while(curr < forward) {
            lex[c] = *curr;
            c++;
            curr++;
        }
    }
    else {
        while(curr < buffers.buffer2 + BUFFERSIZE) {
            lex[c] = *curr;
            c++;
            curr++;
        }
        curr = buffers.buffer1;
        while(curr < forward) {
            lex[c] = *curr;
            c++;
            curr++;
        }
    }
    return lex;
}