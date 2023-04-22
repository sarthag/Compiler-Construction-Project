// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------

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


void print_static_dynamic(symbolTable* entryTable){
    //print all the symbol tables 
    for(int i=0;i<ST_SIZE;i++){

        if(entryTable->symbTable[i]->occupied==1){
            //if the table is occupied 
            if(entryTable->symbTable[i] ->isScope==1){
                //function, conditional or iterative
                print_static_dynamic(entryTable->symbTable[i] ->scopePointer);
            }
            else {
                //primitive or array type
                if(entryTable->symbTable[i] ->entry_DT.isArray==1){
                    if(entryTable->symbTable[i] ->entry_DT.varType.arr.isDynamic){
                        
                        printf("1. Module: %s\t", entryTable->tableName);
                        printf("2. Scope: [%d, %d]\t", entryTable->scopeBeginLine, entryTable->scopeEndLine);
                        printf("3. Variable Name: %s \t", entryTable->symbTable[i]->name);
                        printf("4. Statac or dynamic: Dynamic\t");
                        printf("5. Range Variables: [%s, %s]", entryTable->symbTable[i]->entry_DT.varType.arr.lowerBound.variable, entryTable->symbTable[i]->entry_DT.varType.arr.upperBound.variable);
                        printf("6. Element Type: %s\t", d_type[entryTable->symbTable[i]->entry_DT.varType.arr.arraydType]);
    

                    }
                    else{
                        printf("1. Module: %s\t", entryTable->tableName);
                        printf("2. Scope: [%d, %d]\t", entryTable->scopeBeginLine, entryTable->scopeEndLine);
                        printf("3. Variable Name: %s \t", entryTable->symbTable[i]->name);
                        printf("4. Statac or dynamic: Static\t");
                        printf("5. Range Index: [%d, %d]", entryTable->symbTable[i]->entry_DT.varType.arr.lowerBound.bound, entryTable->symbTable[i]->entry_DT.varType.arr.upperBound.bound);
                        printf("6. Element Type: %s\t", d_type[entryTable->symbTable[i]->entry_DT.varType.arr.arraydType]);
                        

                    }
                    
                }
                else{
                    // variable
                    continue;
                }
                
            }
        }
    }
    printf("Finished printing the static and dynamic %s\n", entryTable->tableName);
}


void printAllSD(symbolTable* table){
    printf("Printing The Static and Dynamic\n");
    print_static_dynamic(table);
}


void activationSizes(symbolTable* table){
    printf("Activation record sizes\n");
    int activationSize;
    symbolTable* funcTable;
    for(int i=0; i<ST_SIZE; i++){
        activationSize = 0;

        if(table->symbTable[i]->entryType == FUNCTION){
            funcTable = table->symbTable[i]->scopePointer;
            for(int j=0; j<ST_SIZE; j++){
                activationSize += funcTable->symbTable[j]->width;
            }

            printf("%s\t%d", table->symbTable[i]->name, activationSize);
        }
    }
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
    printf("5. Symbol Table Records\n");
    printf("6. Activaton Record Sizes of Functions\n");
    printf("7. Static and Dynamic Arrays\n");
    printf("8. Errors and Time analysis\n");
    printf("9. Code Generation (Not Completed)\n");
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
            ast_traversal(ASTroot->leftChild);// prints results of the AST
            printf("Number of nodes in the ast tree: %d\n", astNodes);
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
            printf("Total size of parse tree = %d\n", ptSize);

            astNodes = 0;
            countASTNodes(ASTroot->leftChild);
            printf("\nFor AST :--\n");
            int astSize = astNodes*sizeof(astNode);
            printf("Number of nodes = %d\n", astNodes);
            printf("Size of each node = %lu\n", sizeof(astNode));
            printf("Total size of ast = %d\n", astSize);

            int compression = ((ptSize-astSize) * 100) / ptSize;
            printf("\nCompression Percentage = %d%%", compression);

            break; 

        case 5: // symbol table
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
            ast_traversal(ASTroot);
            initSymbolTable(ASTroot);
            // printAllST(globalTable);
            break; 

        case 6: //activation record size
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
            ast_traversal(ASTroot);
            initSymbolTable(ASTroot);
            activationSizes(globalTable);
            break;

        case 7: // static and dynamic arrays 
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
            ast_traversal(ASTroot);
            initSymbolTable(ASTroot);
            printAllSD(globalTable);
            break;

        case 8: // errors and total compilation time 
            start_time = clock();
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
            ast_traversal(ASTroot);
            initSymbolTable(ASTroot);
            end_time = clock();
            total_CPU_time = (double) (end_time - start_time);
            total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;
            printf("Total CPU Time: %f seconds\n", total_CPU_time_in_seconds);
            break; 
        case 9: // code generation
            printf("Code Generation not completed, Refer codeGen.c for the logic!!");
            break; 
        default:
            break;
        }
        
    }
    
}