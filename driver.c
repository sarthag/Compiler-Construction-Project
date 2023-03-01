#include <stdio.h>
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
    printf("First and Follow Set Automated\n Both Lexical and Syntax analysis modules implemented\n");
    int s;
    char* filename = "testcode";
    scanf("%d", &s);
    while (s != 0)
    {
        switch (s)
        {
        case 1:     //prints comment free code
            /* code */
            removeComments(filename);
            break;
        case 2:
                 // prints lexer results
            FILE* code = readFile(filename);
            getNextToken(code);
            printtokenLL(tokenList);
            break;
        case 3:   //prints all lexical and syntatic errors, prints parse tree
            FILE* code = readFile(filename);
            getNextToken(code);
            break;
        case 4:         //prints total time taken

            break;
        default:
            break;
        }
    }
    
}