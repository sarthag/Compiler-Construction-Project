#include "lexer.h"

int main(){
    FILE* code;
    code = readFile("testcode.txt");
    token t = getNextToken(code);
    printf("%d", t.tid);
}
