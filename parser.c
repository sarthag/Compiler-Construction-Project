#include "parser.h"
#include "adt.h"

//populate fake values of first and follow
bool first[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS+1] = {{1,1,0,1}, {1,1,0,1}, {0,1,0,1}, {0,0,1,0}};
bool follow[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS+1] = {{0,0,0,1}, {0,1,1,0}, {0,0,1,0}, {0,0,0,1}};

void populate_parse_table(){
    //populate the table with -1 
    for(int i=0;i<NUM_OF_NONTERMINALS;i++){
        for(int j=0;j<PT_COLS;j++){
            parse_table[i][j]=-1;
        }
    }
    for(int i=0;i<NUM_OF_RULES;i++){
        bool *first_set= first[G[i].lhs_id];
        for(int j=0; j<NUM_OF_TERMINALS-1;j++){
            if(first_set[j]==1){
                parse_table[G[i].lhs_id][j]=i+1;
            }
        } 
        if(first_set[NUM_OF_TERMINALS-1]==1){
            //if the first set contains epsilon
            bool* follow_set= follow[G[i].lhs_id];
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
    push(parserStack, TERMINAL, $);
    push(parserStack, NON_TERMINAL,start);
    parseTree = create_parse_tree();
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
                pop(parserStack);           //make node in parse tree, copy token information
                L = getNextTk(tokenList, L);
            }
            else{
                printf("Terminal Mismatch"); //implement syncronisation set
            }
        }
        else if (x->type == NON_TERMINAL){
            if (parse_table[x->element.nt.nid][L->tid] != 0){
                pop(parserStack);
                rhs * toPush = G[parse_table[x->element.nt.nid][L->tid]].lastRHS; 
                while (toPush->prevRHS != NULL)
                {
                    push(parserStack, toPush->isTerminal, toPush->rhs_id);
                    toPush = toPush->prevRHS;
                }
                push(parserStack, toPush->isTerminal, toPush->rhs_id);
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
    generateGrammar();
    populate_parse_table();

    parse_code();
    return 0;
}
