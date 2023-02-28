#include "lexer.h"

void printtokenLL(tokenLL tkll){
    printf("Token Count : %d\n",tkll.tokenCount);
    token* tk = tkll.start;
    while(tk !=NULL){
        switch(tk -> tid){
            case(RNUM):
                printf("|ID: %02d | RNUM: |%f| \t LineNo: %d |\n",tk->tid,tk -> rnum , tk -> line_no);
                break;
            case(NUM):
                printf("|ID: %02d | NUM: |%d| \t LineNo: %d |\n",tk->tid,tk -> num , tk -> line_no);
                break;
            default:
                printf("|ID: %02d | Lexeme: |%s| \t LineNo: %d |\n",tk->tid,tk -> lexeme , tk -> line_no);
                break;

        }
        tk = tk ->next;
    }
    printf("NULL\n");
}

int main(){
    populate_keyword_table(keyword_table, KTSIZE);
    // printKeywordTable(keyword_table, KTSIZE);
    FILE* code;
    code = readFile("C://Users//Shaz//Compiler-Construction-Project//test_cases (stage_1)//t5.txt");
    token t = getNextToken(code);
    printf("Lexeme Count: %d\n", lexemeCount);
    printtokenLL(tokenList);

}
