#include "parser.h"
#include "adt.h"

//populate fake values of first and follow
/*
bool first[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS+1] = {{1,1,0,1}, {1,1,0,1}, {0,1,0,1}, {0,0,1,0}};
bool follow[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS+1] = {{0,0,0,1}, {0,1,1,0}, {0,0,1,0}, {0,0,0,1}};
*/

void populate_parse_table(){
    //populate the table with -1 
    for(int i=0;i<NUM_OF_NONTERMINALS;i++){
        for(int j=0;j<PT_COLS;j++){
            parse_table[i][j]=-1;
        }
    }
    for(int i=0;i<NUM_OF_RULES;i++){
        bool first_set[NUM_OF_TERMINALS] = {0}; 
        for(int j = 0; j < NUM_OF_TERMINALS; j++)
            first_set[j] = First[G[i].lhs_id][j];
        for(int j=0; j<NUM_OF_TERMINALS-1;j++){
            if(first_set[j]==1){
                parse_table[G[i].lhs_id][j]=i+1;
            }
        } 
        if(first_set[NUM_OF_TERMINALS-1]==1){
            //if the first set contains epsilon
            bool* follow_set= Follow[G[i].lhs_id];
            for(int k=0;k<NUM_OF_TERMINALS;k++){
                if(follow_set[k]==1){
                    parse_table[G[i].lhs_id][k]=i+1;
                }
            }
        }
    }
}

void InitializeParser(){
    parserStack = (stack*) malloc(sizeof(stack));
    initStack(parserStack);
    push(parserStack, TERMINAL, $, NULL);
    push(parserStack, NON_TERMINAL, start, parseTree->root);
    parseTree = create_parse_tree();
    parseTree->root = create_node(NON_TERMINAL, start);
    L = NULL;
}


token * getNextTk(tokenLL tokenList, token * current){
    if (current == NULL){
        return tokenList.start;
    }
    return current->next;
}

void parse_code(){
    L = getNextTk(tokenList, L);
    while(L != NULL){
        stack_node* x = parserStack->top;
        if (x->type == TERMINAL){
            if (x->element.t.tid == L->tid){
                pop(parserStack);           
                L = getNextTk(tokenList, L);
            }
            else{
                printf("Terminal Mismatch"); //implement syncronisation set
            }
        }
        else if (x->type == NON_TERMINAL){
            if (parse_table[x->element.nt.nid][L->tid] != 0){
                stack_node* parent = pop(parserStack);
                rhs * toPush = G[parse_table[x->element.nt.nid][L->tid]].lastRHS; 
                while (toPush->prevRHS != NULL)
                {   
                    tree_node * temp = create_node(toPush->isTerminal, toPush->rhs_id);
                    insert_child(x->treeLocation, temp);
                    push(parserStack, toPush->isTerminal, toPush->rhs_id, temp);
                    toPush = toPush->prevRHS;
                }
                tree_node * temp = create_node(toPush->isTerminal, toPush->rhs_id);
                insert_child(x->treeLocation, temp);
                push(parserStack, toPush->isTerminal, toPush->rhs_id, x->treeLocation);
            }
            else{
                printf("Non terminal doesnt exist");
            }
        }
        else if (x == NULL){
            printf("Stack empty");
        }
        else{
            continue;
        }

    }
    if(parserStack->top != NULL){
        printf("stack not empty");
    }
}


int main(){
    computeFirstandFollow();
    populate_parse_table();

    parse_code();
    return 0;
}
