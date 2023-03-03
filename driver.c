#include <stdio.h>
#include <time.h>
#include "lexer.h"
#include "parser.h"

void printtokenLL(tokenLL tkll){
    printf("Token Count : %d\n",tkll.tokenCount);
    token* tk = tkll.start;
    while(tk != tkll.end -> next){
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
    printf("0. EXIT\n");
    printf("1. Code without comments\n");
    printf("2. Results if lexical analysis\n");
    printf("3. Results of compilation\n");
    printf("4. Time analysis\n");
    int s;
    char* filename = "t2";
    FILE* prog; 
    clock_t start_time, end_time, t;
    double total_CPU_time, total_CPU_time_in_seconds;
    // s = 3;
    while (s != 0){
        printf("\n");
        printf("Enter option: ");
        scanf("%d", &s);
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
            prog = readFile(filename);
            populate_keyword_table();
            getNextToken(prog);
            printtokenLL(tokenList);
            break;
        case 3:   //prints all lexical and syntatic errors, prints parse tree
            prog = readFile(filename);
            populate_keyword_table();
            getNextToken(prog);
            InitializeParser();
            parse_code();
            print_parse_tree(parseTree->root);
            break;
        case 4:         //prints total time taken
            start_time = clock();
            prog = readFile(filename);
            populate_keyword_table();
            getNextToken(prog);
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