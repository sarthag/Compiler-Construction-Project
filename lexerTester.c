#include "lexer.h"

void printtokenLL(tokenLL tkll){
    printf("Token Count : %d\n",tkll.tokenCount);
    token* tk = tkll.start;
    while(tk !=NULL){
        printf("|TokenID: %d ; Token Lexeme: ; Token LineNo : %d | -> ",tk->tid,tk -> line_no);
        tk = tk -> next;
    }
    printf("NULL\n");
}

int main(){
    populate_keyword_table(keyword_table, KTSIZE);
    printKeywordTable(keyword_table, KTSIZE);
    FILE* code;
    code = readFile("testcode");
    token t = getNextToken(code);
    printf("Token ID: %d\n", t.tid);
    printtokenLL(tokenList);

}
