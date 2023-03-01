#include "lexer.h" 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// #ifndef LL1_GRAMDEF_H
// #define LL1_GRAMDEF_H

typedef struct rhs_struct{
    int rhs_id;
    bool isTerminal;
    struct rhs_struct* nextRHS;
    struct rhs_struct* prevRHS;
} rhs;

typedef struct lhs_struct{
    int lhs_id;
    rhs* firstRHS;
    rhs* lastRHS; 
} lhs; 

#define MAX_LINE_LENGTH 50
#define NUM_OF_RULES 7
#define NUM_OF_TERMINALS 4
#define NUM_OF_NONTERMINALS 4

typedef enum {
    first
} nt_key;

char* nt_list[] = {
    "first"
};


char* token_list[] = {
    "MINUS", "NE", "BO", "BC", "MUL", "COMMENTMARK", "COMMA", "RANGEOP", "DIV", "COLON", "ASSIGNOP", "SEMICOL", "SQBO", "SQBC", "PLUS", "LT", "DEF", "DRIVERDEF", "LE", "EQ", "GT", "GE", "ENDDEF", "DRIVERENDDEF", "NUM", "RNUM", "ID", "AND", "ARRAY", "BOOLEAN", "BREAK", "CASE", "DECLARE", "DEFAULT", "DRIVER", "END", "FOR", "GET_VALUE", "IN", "INPUT", "INTEGER", "MODULE", "OF", "OR", "PARAMETERS", "PRINT", "PROGRAM", "REAL", "RETURNS", "START", "SWITCH", "TAKES", "USE", "WHILE", "WITH", "FALSE", "TRUE"
};

typedef enum {
    NUM1, ID1, COLON1, EPSILON1
}tkls;

char* terms[] = {"NUM1", "ID1", "COLON1", "EPSILON1"};

typedef enum {
    start, module, otherModules, moduleDef
}ntls;

char* nts[] = {"start", "module", "otherModules", "moduleDef"};



typedef struct nonTerminal{
    nt_key nid;
} non_terminal; 


typedef enum {
    NON_TERMINAL,
    TERMINAL
} node_type;


typedef struct stack_node {
    node_type type;
    union {
        non_terminal nt;
        token t;
    } element;
    struct stack_node *next;
    struct tree_node *treeLocation;
} stack_node;


typedef struct Stack {
    int size;
    stack_node *top;
} stack;



//TREE
// need is visited and union of both
// use node type
typedef struct tree_node {
    union {
        non_terminal nt;
        token t;
    } element;
    node_type type;
    struct tree_node *parent;
    struct tree_node *left_child;
    struct tree_node *right_sibling;
    int is_visited;
} tree_node;

typedef struct parse_tree {
    tree_node *root;
} parse_tree;

#define PT_COLS 4

bool First[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
bool firstDone[NUM_OF_NONTERMINALS];
bool Follow[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS] = {0};
bool sync_set[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];

void findFirst(lhs target);
void findFollow(lhs start, rhs *target, rhs *temp);
void computeFirstandFollow();
void syncronization_set();



int parse_table[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS+1];
//array of follow and first
stack* parserStack;
parse_tree* parseTree;
token * L;


lhs G[NUM_OF_RULES];
int get_id(char *str, int t);
bool isTerm(char* str);
void generateGrammar();

void initStack(stack* s);
stack_node* create_stack_node(node_type type, void* element, tree_node* treeLocation);
void push(stack* s, node_type type, int id, tree_node* treeLocation);
stack_node* pop(stack* s);


//Tree
parse_tree *create_parse_tree();
tree_node *create_node(node_type type, int id);
void insert_child(tree_node *parent, tree_node *child);
void set_sibling(tree_node *node, tree_node *sibling);
void set_parent(tree_node *node, tree_node *parent);
void delete_node(tree_node *node);
void inorder_traversal(tree_node *node);

void generateGrammar(); 
//read fake txt file
//first symbol to lhs and rest to rhs
//populate the array 

void computeFirstandFollow();

void createParseTable();

bool isTerm(char* str);


char *non_terminals[]={"start", "module", "otherModules", "moduleDef"};
char *terminals[]={"NUM1", "ID1", "COLON1", "EPSILON1"};

int get_id(char *str, int t){
    //printf("call to get id ");
    //t= 0 for non terminal and 1 and terminal
    //the id for epsilong is -1
    //id returned is -2 if it isn't detected 
    if(strcmp(str, "epsilon")==0){
        return -1;
    }
    if(t==0){
        for(int i=0;i< NUM_OF_NONTERMINALS; i++ ){
            if(strcmp(non_terminals[i], str)==0){
                //printf("strcmp value %d ", strcmp(non_terminals[i], str));
                //printf("%s \n", non_terminals[i]);
                return i;
            }
        //printf("%s non_terminal : Symbol doesn't exist %s \n", str, non_terminals[i]);
        }
    }
    else {
        for(int i=0;i< NUM_OF_TERMINALS; i++ ){
        if(strcmp(terminals[i], str)==0){
            return i;
        }
        //printf("%s terminal : Symbol doesn't exist %s \n", str, terminals[i]);
    }
    }
    printf("not detected \n");
    return -2;
    
}


bool isTerm(char* str){
    if(str[0] >= 65 && str[0]<= 90){
        return 1;
    }
    else if(str[0]>=97 && str[0]<=122){
        return 0;
    }
    return -1;
}


void generateGrammar(){
    FILE *fp = fopen("grammar_fake.txt", "r");
    if(fp ==NULL){
        printf("Error in opening the file ");
    }
    char lineBuf[MAX_LINE_LENGTH];
    int rule_no = 0;
    
    while(fgets(lineBuf, sizeof(lineBuf), fp)!=NULL ){
        char *str;
        rhs *firstRHS = NULL;
        rhs *prev_rhs = NULL;

        str=strtok(lineBuf, " \n");
        for(int i = 0; str != NULL; i++){
            if(i==0){
                //lhs
                G[rule_no].lhs_id = get_id(str, 0);
                G[rule_no].firstRHS = NULL;   
            }
            else {
                rhs *new_rhs = (rhs *)malloc(sizeof(rhs));
                new_rhs->isTerminal = isTerm(str);
                new_rhs->rhs_id = get_id(str, new_rhs->isTerminal);
                new_rhs->nextRHS = NULL;
                
                if(prev_rhs==NULL){
                    //first rule of rhs 
                    firstRHS = new_rhs;
                }
                else{
                    //other rules of rhs
                    prev_rhs->nextRHS = new_rhs;
                }
                
                new_rhs->prevRHS = prev_rhs;
                prev_rhs = new_rhs;
                
            }
            str=strtok(NULL, " \n");
        }
        G[rule_no].firstRHS = firstRHS;
        G[rule_no].lastRHS = prev_rhs;
        rule_no++;
    }


}


void initStack(stack* s) {
    s->top = NULL;
    s->size = 0; 
}

void * makeElement(node_type type, int id){
    if (type == NON_TERMINAL){
        non_terminal * element = (non_terminal *)malloc(sizeof(non_terminal));
        element->nid = id;
        return element;
    }
    else if (type == TERMINAL){
        token * element = (token *)malloc(sizeof(token));
        element->tid = id;
        return element;
    }
    return NULL;
}



stack_node* create_stack_node(node_type type, void* element, tree_node* treeLocation) {
    stack_node* new_node = (stack_node*) malloc(sizeof(stack_node));
    new_node->type = type;
    if (type == TERMINAL) {
        new_node->element.t = *(token*)element;
    } 
    
    else {
        new_node->element.nt = *(non_terminal*)element;
    }
    new_node->treeLocation = treeLocation;
    new_node->next = NULL;
    return new_node;
}


void push(stack* s, node_type type, int id, tree_node* treeLocation) {
    void * element = makeElement(type, id);
    stack_node* new_node = create_stack_node(type, element, treeLocation);
    new_node->next = s->top;
    s->top = new_node;
    s->size++;
}


stack_node* pop(stack* s) {
    if (s->size == 0) {
        return NULL;
    }

    stack_node* top_node = s->top;
    stack_node* temp = top_node;
    s->top = s->top->next;
    free(top_node);
    s->size--;

    return temp;
}



//Parse Tree
parse_tree *create_parse_tree() {
    parse_tree *tree = malloc(sizeof(parse_tree));
    tree->root = NULL;
    return tree;
}

tree_node *create_node(node_type type, int id) {
    void * element = makeElement(type, id);
    tree_node *new_node = (tree_node*) malloc(sizeof(tree_node));
    new_node->type = type;
    if (type == TERMINAL) {
        new_node->element.t = *(token*)element;
    } 
    
    else {
        new_node->element.nt = *(non_terminal*)element;
    }
    new_node->parent = NULL;
    new_node->left_child = NULL;
    new_node->right_sibling = NULL;
    new_node->is_visited = 0;
    return new_node;
}

void insert_child(tree_node *parent, tree_node *child) {
    child->parent = parent;
    if (parent->left_child == NULL) {
        parent->left_child = child;
    } 
    
    else {
        tree_node *sibling = parent->left_child;
        while (sibling->right_sibling != NULL) {
            sibling = sibling->right_sibling;
        }
        sibling->right_sibling = child;
    }
}


void set_sibling(tree_node *node, tree_node *sibling) {
    sibling->parent = node->parent;
    if (node->right_sibling == NULL) {
        node->right_sibling = sibling;
    }
    else {
        set_sibling(node->right_sibling, sibling);
    }
}


void set_parent(tree_node *node, tree_node *parent) {
    if (node != NULL) {
        node->right_sibling = NULL;
        if (parent != NULL) {
            insert_child(parent, node);
        }
    }
}

void delete_node(tree_node *node) {
    if (node->left_child != NULL) {
        delete_node(node->left_child);
    }
    if (node->right_sibling != NULL) {
        delete_node(node->right_sibling);
    }
    free(node);
}

void inorder_traversal(tree_node *node) {
    if (node == NULL) {
        return;
    }
    if (node->type == NON_TERMINAL) {
        printf("%s ", nts[node->element.nt.nid]); // change this back
    } else {
        printf("%s ", terms[node->element.t.tid]); // change this back
    }
    node->is_visited = 1;
    inorder_traversal(node->left_child);
    inorder_traversal(node->right_sibling);
}


void print_parse_tree(parse_tree *tree) {
    inorder_traversal(tree->root);
    printf("\n");
}

void findFirst(lhs target){
    rhs *temp = target.firstRHS;
    if (temp->isTerminal == 1){
        if(temp->rhs_id == NUM_OF_TERMINALS - 1){          // assuming EPSILON id = 3
            rhs* temp2 = temp->nextRHS;
            if(temp2 != NULL){           
            int i = 0;
            for(i; i < NUM_OF_RULES; i++){
                if(G[i].lhs_id == temp2->rhs_id){
                    break;
                }
            }
            
            findFirst(G[i]);
            for(int i = 0; i < NUM_OF_TERMINALS; i++){
                if (First[temp->rhs_id][i] == 1)
                First[target.lhs_id][i] = First[temp->rhs_id][i];
                firstDone[target.lhs_id] = 1;
            }
            }
        }
        First[target.lhs_id][temp->rhs_id] = 1;
        firstDone[target.lhs_id] = 1;
    }
    else{
        if (firstDone[temp->rhs_id] == 0){
            int i = 0;
            for(i; i < NUM_OF_RULES; i++){
                if(G[i].lhs_id == temp->rhs_id){
                    break;
                }
            }
            
            findFirst(G[i]);
        }
        for(int i = 0; i < NUM_OF_TERMINALS; i++){
            if(First[temp->rhs_id][i] == 1)
            First[target.lhs_id][i] = First[temp->rhs_id][i];
            firstDone[target.lhs_id] = 1;
        }
    }
}

void findFollow(lhs start, rhs *target, rhs *temp){
    if (target->isTerminal == 1){
        return;
    }
    if(temp == NULL){
        for(int i =0; i < NUM_OF_TERMINALS; i++){
            Follow[target->rhs_id][i] = Follow[start.lhs_id][i];
        }
        return; 
    }
    if (temp->isTerminal == 1){
        Follow[target->rhs_id][temp->rhs_id] = 1;
        return;
    }
    for(int i =0; i < NUM_OF_TERMINALS - 1; i++){
        if (First[temp->rhs_id][i] == 1){
            Follow[target->rhs_id][i] = First[temp->rhs_id][i];
        }
    }
    if(First[temp->rhs_id][NUM_OF_TERMINALS - 1] == 0){
        return;
    }
    rhs *temp2 = temp->nextRHS;
    if(temp2 == NULL){
        for(int i =0; i < NUM_OF_TERMINALS; i++){
            if (Follow[start.lhs_id][i] == 1)
            Follow[target->rhs_id][i] = Follow[start.lhs_id][i];
        }
        return; 
    }
    findFollow(start, target, temp2);

}


void computeFirstandFollow(){
    //lhs G1[NUM_OF_RULES];
    //G1= generateGrammar();
    generateGrammar();

    for(int j = NUM_OF_RULES - 1; j >= 0; j--){
        findFirst(G[j]);
    }

    for (int j = 0; j < 4; j++){
        printf("\n%d\n%d\n", j, firstDone[j]);

        for(int i = 0; i < NUM_OF_TERMINALS; i++){
            printf("%d", First[j][i]);
        }
    }

    Follow[0][NUM_OF_TERMINALS - 1] = 1;

    for(int j = 0; j < NUM_OF_RULES; j++){
        rhs * target = G[j].firstRHS;
        while (target != NULL)
        {
            rhs * temp = target->nextRHS;
            findFollow(G[j], target, temp); 
            target = temp;
        }       
    }

    for (int j = 0; j < NUM_OF_NONTERMINALS; j++){
        printf("\n");
        for(int i = 0; i < NUM_OF_TERMINALS; i++){
            
            printf("%d", Follow[j][i]);
        }      
    }
}

void synchronization_set(){
    computeFirstandFollow();
    token_key semicol = SEMICOL, bc = BC, sqbc = SQBC;

    for(int i=0; i<=NUM_OF_NONTERMINALS; i++){
        for(int j=0; j<=NUM_OF_TERMINALS; j++){
            sync_set[i][j] = (j == semicol) || (j == bc) || (j == sqbc) || First[i][j] || Follow[i][j];
        }
    }
}


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









// #endif