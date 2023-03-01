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
    push(parserStack, NON_TERMINAL, program, parseTree->root);
    parseTree = create_parse_tree();
    parseTree->root = create_node(NON_TERMINAL, program);
    L = NULL;
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
            return;
        }
        L = getNextTk(tokenList, L);
    }
}

void parse_code(){
    L = getNextTk(tokenList, L);
    // stack_node* s;
    while(L != NULL){
        stack_node* x = parserStack->top;
        if (x->type == TERMINAL){
            if (x->element.t.tid == L->tid){
                pop(parserStack);
                L = getNextTk(tokenList, L);                
            }
            else{
                pop(parserStack);
                printf("ERROR : Terminal Mismatch"); 
          }
            
        }
        else if (x->type == NON_TERMINAL){
            if (parse_table[x->element.nt.nid][L->tid] != -1){
                pop(parserStack);
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
                printf("ERROR : Non terminal doesnt exist");
                parser_retract(x ->element.nt,L);
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
void synchronization_set(){
    // computeFirstandFollow();
    token_key semicol = SEMICOL, bc = BC, sqbc = SQBC;

    for(int i=0; i<=NUM_OF_NONTERMINALS; i++){
        for(int j=0; j<=NUM_OF_TERMINALS; j++){
            sync_set[i][j] = (j == semicol) || (j == bc) || (j == sqbc) || First[i][j] || Follow[i][j];
        }
    }
}

void inorder_traversal(tree_node *node, FILE* fp) {
    if (node == NULL) {
        return;
    }
    if (node->type == NON_TERMINAL) {
        fprintf(fp, "%s ", nt_list[node->element.nt.nid]); // change this back
    } 
    else {
        fprintf(fp, "%s ", token_list[node->element.t.tid]); // change this back
    }
    node->is_visited = 1;
    inorder_traversal(node->left_child, fp);
    inorder_traversal(node->right_sibling, fp);
}

FILE* print_parse_tree(tree_node *node){
    FILE *fp = fopen("parse_tree.txt", "w");
    inorder_traversal(node, fp);
    return fp;
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