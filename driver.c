#include <stdio.h>
#include <time.h>
#include "lexer.h"
#include "parser.h"

void printtokenLL(tokenLL tkll){
    printf("Token Count : %d\n",tkll.tokenCount);
    token* tk = tkll.start;
    while(tk !=NULL){
        switch(tk -> tid){
            case(RNUM):
                printf("|LineNo: %d | RNUM: |%f| \t ID: %02d |\n", tk -> line_no,tk -> rnum ,tk->tid);
                break;
            case(NUM):
                printf("|LineNo: %d | NUM: |%d| \t ID: %02d |\n", tk -> line_no,tk -> num , tk->tid);
                break;
            default:
                printf("|LineNo: %d | Lexeme: |%s| \t ID: %02d |\n", tk -> line_no,tk -> lexeme , tk->tid);
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
        clock_t t;
        t = clock();
        switch (s)
        {
        case 0:
            exit(0);
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
            InitializeParser();
            parse_code();
            print_parse_tree(parseTree->root);
            break;
        case 4:         //prints total time taken
            clock_t start_time, end_time;
            double total_CPU_time, total_CPU_time_in_seconds;
            start_time = clock();
            FILE* code = readFile(filename);
            getNextToken(code);
            InitializeParser();
            parse_code();
            end_time = clock();
            total_CPU_time = (double) (end_time - start_time);
            total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;
            printf("Total CPU Time: %f seconds\n", total_CPU_time_in_seconds);
            break;
        default:
            break;
        }
    }
    
}