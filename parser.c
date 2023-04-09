// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------


#include "parser.h"

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
    synchronization_set();
    populate_parse_table();
    parserStack = (stack*) malloc(sizeof(stack));
    initStack(parserStack);
    parseTree = create_parse_tree();
    parseTree->root = create_node(NON_TERMINAL, program);
    parseTree -> root ->rule = 0;
    parseTree -> root ->type = NON_TERMINAL;
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
        if(parse_table[nonterm.nid][EPSILON]){
            pop(parserStack);
            // printStack(parserStack);
            return;
        }
        L = getNextTk(tokenList, L);
    }
}

void parse_code(){
    int c = 0;
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
            printf("Rule No from PT: %d\n",(parse_table[x->element.nt.nid][L ->tid])+1);
            if (parse_table[x->element.nt.nid][L->tid] != -1){
                x = pop(parserStack);
                //printStack(parserStack);
                // printf("%d %d %d\n", x->element.nt.nid, L->tid, G[parse_table[x->element.nt.nid][L->tid]].lastRHS->rhs_id);
                rhs* toPush = G[parse_table[x->element.nt.nid][L->tid]].lastRHS;
                int ruleNo = parse_table[x->element.nt.nid][L->tid];
                x->treeLocation->rule = ruleNo;

                while (toPush->prevRHS!= NULL && toPush->rhs_id != EPSILON){   
               
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
                    insert_child(x->treeLocation, temp);
                    // printf("Inserted into tree: %d",temp ->element.nt.nid);
                    push(parserStack, toPush->isTerminal, toPush->rhs_id, temp);
                    //printStack(parserStack);
                    toPush = toPush->prevRHS;
                }   
                if(toPush->isTerminal ==1 && toPush -> rhs_id == EPSILON){
                    printf("Rule No from Parse Tree element: %d\n",(x->treeLocation->rule)+1);
                    // fprintf(stdout, "----- | %d | no | %d |%d|%d \n", node->parent->element.nt.nid, node->element.nt.nid,node ->rule,node ->type);
                    continue;
                } 
                tree_node* temp = (tree_node*)malloc(sizeof(tree_node));
                    temp = create_node(toPush->isTerminal, toPush->rhs_id);
                    insert_child(x->treeLocation, temp);
                    push(parserStack, toPush->isTerminal, toPush->rhs_id, temp);
                    // printStack(parserStack);
                printf("Rule No from Parse Tree element: %d\n",(x->treeLocation->rule)+1);
                // fprintf(stdout, "----- | %d | no | %d |%d|%d \n",x->treeLocation->parent->element.nt.nid, node->element.nt.nid,node ->rule,node ->type);

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

        printf("\nAFTER:");
        printStack(parserStack);
        printf("==================\n");
    }

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
