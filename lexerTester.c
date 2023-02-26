#include "lexer.h"

void printtokenLL(tokenLL tkll){
    printf("Token Count : %d\n",tkll.tokenCount);
    token* tk = tkll.start;
    while(tk !=NULL){
        switch(tk -> tid){
            case(RNUM):
                printf("|TokenID: %d ; Token RNUM:%f ; Token LineNo : %d |\n",tk->tid,tk -> rnum , tk -> line_no);
                break;
            case(NUM):
                printf("|TokenID: %d ; Token NUM:%d ; Token LineNo : %d |\n",tk->tid,tk -> num , tk -> line_no);
                break;
            default:
                printf("|TokenID: %d ; Token Lexeme:%s ; Token LineNo : %d |\n",tk->tid,tk -> lexeme , tk -> line_no);
                break;

        }
        tk = tk ->next;
    }
    printf("NULL\n");
}

int main(){
    populate_keyword_table(keyword_table, KTSIZE);
    printKeywordTable(keyword_table, KTSIZE);
    FILE* code;
    code = readFile("testcode");
    token t = getNextToken(code);
    printf("Lexeme Count: %d\n", lexemeCount);
    printtokenLL(tokenList);

}
