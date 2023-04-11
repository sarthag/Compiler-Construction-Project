#include <stdio.h>
#include <time.h>
#include "symbolTable.h"

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

int main(int argc, char* argv[]){
    if(argc != 3) {
        printf("Incorrect Number of Arguments!!");
        return 0;
    }
    char* filename = argv[1];
    //char* parseTreeFile = argv[2];
    int BUFFSIZE = atoi(argv[2]);
    printf("First and Follow Set Automated\n Lexical, Syntax and Semantic analysis modules implemented\n");
    printf("0. EXIT\n");
    printf("1. Results if lexical analysis\n");
    printf("2. Results of compilation\n");
    printf("3. Results of AST creation\n");
    printf("4. AST Space Efficiency\n");
    printf("5. \n");
    printf("6. \n");
    printf("7. \n");
    printf("8. \n");
    printf("9. \n");
    int s;
    // char* filename = "test_cases (stage_1)/t6(with_syntax_errors).txt";
    FILE* prog; 
    clock_t start_time, end_time, t;
    double total_CPU_time, total_CPU_time_in_seconds;
    astNode* ASTroot;
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
        case 1: // prints lexer results
            prog = readFile(filename);
            populate_keyword_table();
            getNextToken(prog);
            printtokenLL(tokenList);
            break;
        case 2:  //prints all lexical and syntatic errors, prints parse tree
            prog = readFile(filename);
            populate_keyword_table();
            getNextToken(prog);
            InitializeParser();
            parse_code();
            printf("Printing Preorder Traversal of Parse tree (Parent->left Child->Right Child\n");
            printParseTree(parseTree->root, "parseTree.txt");
            printf("Number of nodes in the parse tree: %d\n", parse_tree_nodes);
            break;
        case 3: 
            removeComments(filename);
            prog = readFile(filename);
            populate_keyword_table();
            getNextToken(prog);
            InitializeParser();
            parse_code();
            syntaxStack = initAST();
            ASTroot = createASTNode(NON_TERMINAL, -1, parseTree->root);
            topDownPass(ASTroot, parseTree->root, syntaxStack);    
            callfindAction(ASTroot, syntaxStack);
            ast_traversal(ASTroot);// prints results of the AST
            
            break; 

        case 4:
            removeComments(filename);
            prog = readFile(filename);
            populate_keyword_table();
            getNextToken(prog);
            InitializeParser();
            parse_code();
            syntaxStack = initAST();
            ASTroot = createASTNode(NON_TERMINAL, -1, parseTree->root);
            topDownPass(ASTroot, parseTree->root, syntaxStack);    
            callfindAction(ASTroot, syntaxStack);
            parse_tree_nodes = 0;
            countPTNodes(parseTree->root);
            printf("For Parse Tree :--\n");
            int ptSize = parse_tree_nodes*sizeof(tree_node);
            printf("Number of nodes = %d\n", parse_tree_nodes);
            printf("Size of each node = %lu\n", sizeof(tree_node));
            printf("Total size of parse tree = %lu\n", ptSize);

            astNodes = 0;
            countASTNodes(ASTroot);
            printf("\nFor AST :--\n");
            int astSize = astNodes*sizeof(astNode);
            printf("Number of nodes = %d\n", astNodes);
            printf("Size of each node = %lu\n", sizeof(astNode));
            printf("Total size of parse tree = %lu\n", astSize);

            int compression = ((ptSize-astSize) * 100) / ptSize;
            printf("\nCompression Percentage = %d %", compression);

            break; 

        case 5: // symbol table
            break; 

        case 6: //activation record size
            break;

        case 7: // static and dynamic arrays 
            break;

        case 8: // errors and total compilation time 
            break; 

        case 9: // code generation -- FUCKED
            break; 
        default:
            break;
        }
        
    }
    
}