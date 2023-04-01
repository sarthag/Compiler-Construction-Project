#include "astadt.h"

void initStack(astStack* s) {
    s->top = NULL;
    s->size = 0; 
}

astStackNode* createastStackNode(astNode *treeloc){
    astStackNode* new = (astStackNode*) malloc(sizeof(astStackNode));
    new -> treeloc = treeloc;
    new -> next = NULL;

    return new; 
}

void pushast(astStack* s, astNode *treeloc){
    astStackNode* node = createastStackNode(treeloc);
    s->size++;
    node->next = s->top; 
    s->top = node;
}

void popast(astStack* s){
    if (s->size == 0) {
        return NULL;
    }

    astStackNode* top = s->top;
    astStackNode* temp = top; 
    s->top = s->top->next;

    s->size--;
    return temp; 
}


ast *createSyntaxTree() {
    ast *tree = malloc(sizeof(ast));
    tree->root = NULL;
    return tree;
}

astNode* createASTNode(labels label, int rule_no, int childast, int )





