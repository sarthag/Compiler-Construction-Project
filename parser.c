// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------


#include "parser.h"

// void synchronization_set(){
//     for(int i=0; i<NUM_OF_NONTERMINALS; i++){
//         for(int j=0; j<NUM_OF_TERMINALS; j++){
//             sync_set[i][j] = (j == SEMICOL) || Follow[i][j];
//         }
//     }
// }

void InitializeParser(){
    populate_grammar();
    generateGrammar();
    computeFirstandFollow();
    //synchronization_set();
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

void parse_code(){
    int prev_err_line = 0; 
    bool popped = false;
    int c = 0;
    while(L != NULL){

        // printf("\nBEFORE:");
        // printStack(parserStack);
        // printf("L -> tkid : %d\n:",L ->tid);
        // printf("Line No:%d\n",L->line_no);

        stack_node* x = parserStack->top;

        if (x->type == TERMINAL){
            //printf("Rule No: %d\n",(parse_table[L ->tid][x->element.t.tid])+1);

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
                if(L->line_no != prev_err_line){
                    if(L->tid == NUM){
                        printf("ERROR at line %d: Unexpected %d\n", L->line_no, L->num);
                    }

                    else if(L->tid == RNUM){
                        printf("ERROR at line %d: Unexpected %f\n", L->line_no, L->rnum);
                    }

                    else{
                        printf("ERROR at line %d: Unexpected %s\n", L->line_no, L->lexeme);
                    }
                    prev_err_line = L->line_no;
                }
        
                pop(parserStack); 
            }    
        }


        else if (x->type == NON_TERMINAL){
            //printf("Rule No %d\n",(parse_table[x->element.nt.nid][L ->tid])+1);

            if (parse_table[x->element.nt.nid][L->tid] != -1){
                x = pop(parserStack);

                rhs* toPush = G[parse_table[x->element.nt.nid][L->tid]].lastRHS;
                int ruleNo = parse_table[x->element.nt.nid][L->tid];

                x->treeLocation->rule = ruleNo;

                while (toPush->prevRHS != NULL && toPush->rhs_id != EPSILON){   
               
                    tree_node* temp = (tree_node*)malloc(sizeof(tree_node));
                    temp = create_node(toPush ->isTerminal, toPush->rhs_id);     
                    insert_child(x->treeLocation, temp);
                    push(parserStack, toPush->isTerminal, toPush->rhs_id, temp);
                    toPush = toPush->prevRHS;
                } 

                if(toPush->isTerminal == 1 && toPush -> rhs_id == EPSILON){
                    continue;
                } 

                tree_node* temp = (tree_node*)malloc(sizeof(tree_node));
                temp = create_node(toPush->isTerminal, toPush->rhs_id);
                insert_child(x->treeLocation, temp);
                push(parserStack, toPush->isTerminal, toPush->rhs_id, temp);
            }

            else{
                if(L->line_no != prev_err_line){
                    if(L->tid == NUM){
                        printf("ERROR at line %d: Unexpected %d\n", L->line_no, L->num);
                    }

                    else if(L->tid == RNUM){
                        printf("ERROR at line %d: Unexpected %f\n", L->line_no, L->rnum);
                    }

                    else{
                        printf("ERROR at line %d: Unexpected %s\n", L->line_no, L->lexeme);
                    }
                    prev_err_line = L->line_no;
                }
              
               if((Follow[parserStack->top->element.nt.nid][L->tid] || L->tid == SEMICOL || L->tid == END) && !popped){
                pop(parserStack);
                popped = true;
                }

                else{
                    L = getNextTk(tokenList, L);  
                    popped = false; 
                }            
            }
        }
        // printf("\nAFTER:");
        // printStack(parserStack);
        // printf("==================\n");
    }

    if(parserStack -> top != NULL && L -> next == NULL){
        printf("ERROR: Linked List empty, stack not empty\n");
    }

    fixParseTree(parseTree->root);
}


void fixParseTree(tree_node* root){
    if(root == NULL || root->type == TERMINAL){
        return; 
    }

    if(root->left_child == NULL){
        tree_node* eps = (tree_node*)malloc(sizeof(tree_node));
        eps = create_node(TERMINAL, EPSILON);
        insert_child(root, eps);
    }

    else{
        fixParseTree(root->left_child);
    }

    fixParseTree(root->right_sibling);
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
