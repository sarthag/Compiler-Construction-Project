// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------


#include "parser.h"

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
    token_key semicol = SEMICOL, bc = BC, sqbc = SQBC;

    for(int i=0; i<NUM_OF_NONTERMINALS; i++){
        for(int j=0; j<NUM_OF_TERMINALS; j++){
            sync_set[i][j] = (j == semicol) || (j == bc) || (j == sqbc) || First[i][j] || Follow[i][j];
        }
    }
}

void InitializeParser(){
    populate_grammar();
    generateGrammar();
    computeFirstandFollow();
    //loadFirstFollow();
    synchronization_set();
    populate_parse_table();
    parserStack = (stack*) malloc(sizeof(stack));
    initStack(parserStack);
    parseTree = create_parse_tree();
    parseTree->root = create_node(NON_TERMINAL, program);
    push(parserStack, TERMINAL, $, NULL);
    push(parserStack, NON_TERMINAL, program, parseTree->root);
    L = tokenList.start ;
    token* lastTK = addTokenToList();
    lastTK ->tid = 57;
    lastTK ->next = NULL;

    // printf("HEAD OF TOKEN LIST : %d", tokenList.start->tid);
}


token * getNextTk(tokenLL tokenList, token * current){
    if (current == NULL){
        return tokenList.start;
    }
    return (current -> next == NULL) ?NULL :current->next;
}


void parser_retract(non_terminal nonterm, token* current) {
    while(!sync_set[nonterm.nid][current ->tid]){
        // stack_node *sn = pop(parserStack);
        if(parse_table[nonterm.nid][EPSILON]){
            pop(parserStack);
            // printStack(parserStack);
            return;
        }
        L = getNextTk(tokenList, L);
    }
}

void parse_code(){
    int c=0;
    // stack_node* s;
    while(L != NULL){
        printf("\nBEFORE:");
        printStack(parserStack);
        printf("L -> tkid : %d\n:",L ->tid);
        printf("Line No:%d\n",L->line_no);
        stack_node* x = parserStack->top;
        if (x->type == TERMINAL){
            printf("Rule No: %d\n",(parse_table[L ->tid][x->element.t.tid])+1);
            if((x->element.t.tid == $ || x == NULL)&& L -> next == NULL){
                printf("Accept!\n");
                pop(parserStack);
                break;
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
             printf("Rule No: %d\n",(parse_table[x->element.nt.nid][L ->tid])+1);
            if (parse_table[x->element.nt.nid][L->tid] != -1){
                x = pop(parserStack);
                //printf("x -> treeLocation is NULL after pop?: %d\n", x->treeLocation== NULL);
                 //printStack(parserStack);
                // printf("%d %d %d\n", x->element.nt.nid, L->tid, G[parse_table[x->element.nt.nid][L->tid]].lastRHS->rhs_id);
                rhs* toPush = G[parse_table[x->element.nt.nid][L->tid]].lastRHS;
                int ruleNo = parse_table[x->element.nt.nid][L->tid];
                x->treeLocation->rule = ruleNo;
                //printf("x -> treeLocation is NULL after rhs?: %d\n", x->treeLocation== NULL);

                while (toPush->prevRHS!= NULL && toPush->rhs_id != EPSILON)
                {   
                    // if(toPush->prevRHS== NULL) {
                    //printf("x -> treeLocation is NULL before temp?: %d\n", x->treeLocation== NULL);
                    tree_node* temp = (tree_node*)malloc(sizeof(tree_node));
                    temp=create_node(toPush ->isTerminal,toPush->rhs_id);
                    temp->element.t.line_no = L->line_no;
                    if(L->tid == NUM) {
                        temp->element.t.num = L->num;                        
                    }
                    else if(L->tid == RNUM) {
                        temp->element.t.rnum = L->rnum;

                    }
                    else {
                        temp->element.t.lexeme = L->lexeme;
                    }
                    temp->element.t.tid = L->tid;      
                    // }          
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
                    //printStack(parserStack);
                    toPush = toPush->prevRHS;
                    //break;
                }   
                if(toPush->isTerminal ==1 && toPush -> rhs_id == EPSILON){
                    continue;
                } 
                tree_node* temp = (tree_node*)malloc(sizeof(tree_node));
                    temp = create_node(toPush->isTerminal, toPush->rhs_id);
                    insert_child(x->treeLocation, temp);
                    push(parserStack, toPush->isTerminal, toPush->rhs_id, x->treeLocation);
                    // printStack(parserStack);
            }
            else{
                printf("ERROR : Non terminal doesnt exist\n");
                for(int i=0; i<NUM_OF_TERMINALS; i++){
                }
                // printf("PRINTING PARSE TABLE ROW FOR THE NON TERMINAL %d:\n",x->element.nt.nid);
                // for(int i = 0 ; i  < NUM_OF_TERMINALS ; i++){
                //     printf("%d ", parse_table[x->element.nt.nid][i]);
                // }

                parser_retract(x ->element.nt,L);
                // break;
            }
        }
        else if (x == NULL){
        }
        else{
            printf("\nAFTER:");
            printStack(parserStack);
            printf("==================\n");
            continue;
        }
        // L = getNextTk(tokenList)
        // c=c+1;
        // if(c==20){
        //     break;
        // }
        printf("\nAFTER:");
        printStack(parserStack);
        printf("==================\n");
    }
    //if((parserStack->top != NULL || parserStack-> top->element.t.tid!=$) && L -> next == NULL ){
    if(parserStack -> top != NULL && L -> next == NULL){
        printf("ERROR: Linked List empty, stack not empty\n");
    }
}




void printParseTree(tree_node *node, char* parseTreeFile){
    FILE *fp = fopen(parseTreeFile, "w");
    if(fp == NULL){
        printf("FILE OPENING ERROR!!!\n");
        return;
    }
    inorder_traversal(node, fp);
    fclose(fp);
}
