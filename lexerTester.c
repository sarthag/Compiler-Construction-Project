#include "lexer.h"

int main(){
    populate_keyword_table(keyword_table, KTSIZE);
    printKeywordTable(keyword_table, KTSIZE);
    FILE* code;
    code = readFile("C://Users//Shaz//Compiler-Construction-Project//test_cases (stage_1)//t1.txt");
    token t = getNextToken(code);
    printf("Token ID: %d\n", t.tid);
}
