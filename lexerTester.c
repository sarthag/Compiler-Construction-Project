#include "lexer.h"

int main(){
    FILE* code;
    code = readFile("testcode");
    token t = getNextToken(code);
    printf("Token ID: %d\n", t.tid);
}
