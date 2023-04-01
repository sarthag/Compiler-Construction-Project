#include "astadt.h"

void initASTStack(astStack* s) {
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

astNode* createASTNode(labels label, int rule_no){
    astNode *new = (astNode*) malloc(sizeof(astNode));
    new -> rule_no = rule_no; 

  
    new->parent = NULL; 
    new->leftChild = NULL; 
    new->rightSibling = NULL; 

    return new; 
}


void insertASTchild(astNode *parent, astNode* child){
    child -> parent = parent; 

    if (parent->leftChild == NULL) {
        parent->leftChild = child;
    } 
    
    else {
        astNode *sibling = parent->leftChild;
        while (sibling->rightSibling != NULL) {
            sibling = sibling->rightSibling;
        }
        sibling->rightSibling = child;
    }
}


void setASTSibling(astNode *node, astNode *sibling) {
    sibling->parent = node->parent;
    if (node->rightSibling == NULL) {
        node->rightSibling = sibling;
    }
    else {
        set_sibling(node->rightSibling, sibling);
    }
}


void setASTparent(astNode *node, astNode *parent) {
    if (node != NULL) {
        node->rightSibling = NULL;
        if (parent != NULL) {
            insert_child(parent, node);
        }
    }
}