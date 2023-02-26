#include "lexer.h"

int main(){
    populate_keyword_table(keyword_table, KTSIZE);
    printKeywordTable(keyword_table, KTSIZE);
    FILE* code;
    code = readFile("testcode");
    token t = getNextToken(code);
    printf("Token ID: %d\n", t.tid);
}
