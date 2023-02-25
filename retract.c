#include "lexer.h"
#include "lexer.h"
#include "lexerDef.h"

void retract(int n) {
    if(forward >= buffers.buffer1 && forward <= buffers.buffer1 + BUFFERSIZE) {
        if(forward - buffers.buffer1 < n) {
            n -= forward - buffers.buffer1;
            forward = buffers.buffer2 + BUFFERSIZE - n;
        }
        else {
            forward -= n;
        }
    }
    else if(forward >= buffers.buffer2 && forward <= buffers.buffer2 + BUFFERSIZE) {
        if(forward - buffers.buffer2 < n) {
            n -= forward - buffers.buffer2;
            forward = buffers.buffer1 + BUFFERSIZE - n;
        }
        else {
            forward -= n;
        }
    }
    numChar -= n;
}