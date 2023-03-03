#include "parser.h"
#include "adt.h"

//populate fake values of first and follow
/*
bool first[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS+1] = {{1,1,0,1}, {1,1,0,1}, {0,1,0,1}, {0,0,1,0}};
bool follow[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS+1] = {{0,0,0,1}, {0,1,1,0}, {0,0,1,0}, {0,0,0,1}};
*/

// void populate_parse_table(){
//     //populate the table with -1 
//     for(int i=0;i<NUM_OF_NONTERMINALS;i++){
//         for(int j=0;j<PT_COLS;j++){
//             parse_table[i][j]=-1;
//         }
//     }
//     for(int i=0;i<NUM_OF_RULES;i++){
//         bool first_set[NUM_OF_TERMINALS] = {0}; 
//         for(int j = 0; j < NUM_OF_TERMINALS; j++)
//             first_set[j] = First[G[i].lhs_id][j];
//         for(int j=0; j<NUM_OF_TERMINALS-1;j++){
//             if(first_set[j]==1){
//                 parse_table[G[i].lhs_id][j]=i+1;
//             }
//         } 
//         if(first_set[NUM_OF_TERMINALS-1]==1){
//             //if the first set contains epsilon
//             bool* follow_set= Follow[G[i].lhs_id];
//             for(int k=0;k<NUM_OF_TERMINALS;k++){
//                 if(follow_set[k]==1){
//                     parse_table[G[i].lhs_id][k]=i+1;
//                 }
//             }
//         }
//     }
// }

void synchronization_set(){
    // computeFirstandFollow();
    token_key semicol = SEMICOL, bc = BC, sqbc = SQBC;

    for(int i=0; i<=NUM_OF_NONTERMINALS; i++){
        for(int j=0; j<=NUM_OF_TERMINALS; j++){
            sync_set[i][j] = (j == semicol) || (j == bc) || (j == sqbc) || First[i][j] || Follow[i][j];
        }
    }
}

void InitializeParser(){
    populate_grammar();
    generateGrammar();
    // computeFirstandFollow();
    loadFirstFollow();
    synchronization_set();
    populate_parse_table();
    parserStack = (stack*) malloc(sizeof(stack));
    initStack(parserStack);
    parseTree = create_parse_tree();
    parseTree->root = create_node(NON_TERMINAL, program);
    push(parserStack, TERMINAL, $, NULL);
    push(parserStack, NON_TERMINAL, program, parseTree->root);
    L = tokenList.start ;
    printf("HEAD OF TOKEN LIST : %d", tokenList.start->tid);
}


token * getNextTk(tokenLL tokenList, token * current){
    if (current == NULL){
        return tokenList.start;
    }
    printf("L = %d\n", current ->tid);
    return (current -> next == NULL) ?NULL :current->next;
}


void parser_retract(non_terminal nonterm, token* current) {
    printf("in retract\n");
    while(!sync_set[nonterm.nid][current ->tid]){
        printf("in retract while\n");
        // stack_node *sn = pop(parserStack);
        if(parse_table[nonterm.nid][EPSILON]){
            printf("epsilon rule gotta go popping\n ");
            pop(parserStack);
            printStack(parserStack);
            return;
        }
        L = getNextTk(tokenList, L);
    }
    printf("retract done");
}

void parse_code(){
    printf("Inside Parser\n");
    printf("HEAD OF TOKEN LIST : %d", tokenList.start->tid);
    printf("L = %d\n", L ->tid);
    int c=0;
    // stack_node* s;
    while(L != NULL){
        printStack(parserStack);
        printf("Inside While\n");
        printf("Token is %d\n", L->tid);
        stack_node* x = parserStack->top;
        if (x->type == TERMINAL){
            printf("X ->terminalvalue: %d\n",x ->element.t.tid);
            if(x->element.t.tid == $ && L -> next == NULL){
                printf("Accept!\n");
            }
            else if(x->element.t.tid == $ && L -> next != NULL){
                printf("ERROR : Input remaining, Stack empty\n");
                break;
            }
            else if (x->element.t.tid == L->tid){
                pop(parserStack);
                L = getNextTk(tokenList, L);                
            }
            else{
                pop(parserStack);
                printf("ERROR : Terminal Mismatch L: %d\n", L->tid); 
          }
            
        }
        else if (x->type == NON_TERMINAL){
            printf("x non terminal\n");
            printf("NON terminal: %d\n",x ->element.nt.nid);
            printf("PARSE TABLE VALUE : %d\n",parse_table[x->element.nt.nid][L->tid]);
            if (parse_table[x->element.nt.nid][L->tid] != -1){
                x = pop(parserStack);
                //printf("x -> treeLocation is NULL after pop?: %d\n", x->treeLocation== NULL);
                printf("PRINTING STACK AFTER POP:\n");
                printStack(parserStack);
                printf("popped\n");
                // printf("%d %d %d\n", x->element.nt.nid, L->tid, G[parse_table[x->element.nt.nid][L->tid]].lastRHS->rhs_id);
                rhs* toPush = G[parse_table[x->element.nt.nid][L->tid]].lastRHS; 
                printf("TO PUSH INTO STACK : %d, %d\n",toPush->isTerminal,toPush->rhs_id);
                //printf("x -> treeLocation is NULL after rhs?: %d\n", x->treeLocation== NULL);

                while (toPush->prevRHS!= NULL && toPush->rhs_id != EPSILON)
                {   
                    if(toPush->prevRHS== NULL)
                        printf("topush->next is NULL");
                    printf("inside while\n");
                    //printf("x -> treeLocation is NULL before temp?: %d\n", x->treeLocation== NULL);
                    tree_node* temp = (tree_node*)malloc(sizeof(tree_node));
                    temp=create_node(toPush ->isTerminal,toPush->rhs_id);
                    //// break;
                    //printf("x -> treeLocation is NULL after temp?: %d\n", x->treeLocation== NULL);
                    //tree_node* temp = NULL;
                    // printf("temp type : %d\n", temp->type);
                    // printf("temp type : %d\n", temp->is_visited);
                    // tree_node* temp = NULL;
                    // printf("To be inserted into tree: %d\n",temp ->element.nt.nid);
                    // printf("x -> treeLocation is NULL after temp?: %d\n", x->treeLocation== NULL);
                    // printf("parseTree -> root : %d\n",parseTree->root->element.nt.nid);
                    insert_child(x->treeLocation, temp);
                    // printf("Inserted into tree: %d",temp ->element.nt.nid);
                    push(parserStack, toPush->isTerminal, toPush->rhs_id, temp);
                    printStack(parserStack);
                    toPush = toPush->prevRHS;
                    //break;
                }   
                printf("while over\n"); 
                if(toPush->isTerminal ==1 && toPush -> rhs_id == EPSILON){
                    printf("epsilon rule\n");
                    continue;
                } 
                tree_node* temp = (tree_node*)malloc(sizeof(tree_node));
                    temp = create_node(toPush->isTerminal, toPush->rhs_id);
                    insert_child(x->treeLocation, temp);
                    push(parserStack, toPush->isTerminal, toPush->rhs_id, x->treeLocation);
                    printStack(parserStack);
                    printf("If over\n");   
            }
            else{
                printf("ERROR : Non terminal doesnt exist\n");
                for(int i=0; i<NUM_OF_TERMINALS; i++){
                    printf("%d ", parse_table[x->element.nt.nid][i]);
                }
                printf("\n");
                // printf("PRINTING PARSE TABLE ROW FOR THE NON TERMINAL %d:\n",x->element.nt.nid);
                // for(int i = 0 ; i  < NUM_OF_TERMINALS ; i++){
                //     printf("%d ", parse_table[x->element.nt.nid][i]);
                // }

                parser_retract(x ->element.nt,L);
                // break;
            }
            printf("x non terminal over\n");
        }
        else if (x == NULL){
            printf("Stack empty");
        }
        else{
            continue;
        }
        // L = getNextTk(tokenList)
        // c=c+1;
        // if(c==20){
        //     break;
        // }
    }
    if(parserStack->top != NULL || parserStack-> top->element.t.tid!=$){
        printf("ERROR: Linked List empty, stack not empty\n");
    }
}




void printParseTree(tree_node *node, char* parseTreeFile){
    FILE *fp = fopen(parseTreeFile, "w");
    inorder_traversal(node, fp);
    fclose(fp);
}

/*
int main(){
    computeFirstandFollow();
    synchronization_set();
    populate_parse_table();

    parse_code();
    return 0;
}
*/

/*
int main(){
    parseTree = create_parse_tree();
    parseTree->root = create_node(NON_TERMINAL, program);
    tree_node * temp = create_node(TERMINAL, 2);
    insert_child(parseTree->root, temp);
    temp = create_node(TERMINAL, 4);
    insert_child(parseTree->root, temp);
    FILE * treeOut = print_parse_tree(parseTree->root);
}
*/