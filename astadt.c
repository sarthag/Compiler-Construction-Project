#include "astadt.h"

void initASTStack(astStack* s) {
    s->top = NULL;
    s->size = 0; 
}

astStackNode* createastStackNode(tree_node *treeloc){
    astStackNode* new = (astStackNode*) malloc(sizeof(astStackNode));
    new -> treeloc = treeloc;
    new -> next = NULL;

    return new; 
}

void pushast(astStack* s, tree_node *treeloc){
    astStackNode* node = createastStackNode(treeloc);
    s->size++;
    node->next = s->top; 
    s->top = node;
}

astStackNode* popast(astStack* s){
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
    new->child.leftChild = NULL; 
    new->nextElm.rightSibling = NULL; 

    return new; 
}


void insertASTchild(astNode *parent, astNode* child){
    child -> parent = parent; 

    if (parent->child.leftChild == NULL) {
        parent->child.leftChild = child;
    } 
    
    else {
        astNode *sibling = parent->child.leftChild;
        while (sibling->nextElm.rightSibling != NULL) {
            sibling = sibling->nextElm.rightSibling;
        }
        sibling->nextElm.rightSibling = child;
    }
}


void setASTSibling(astNode *node, astNode *sibling) {
    sibling->parent = node->parent;
    if (node->nextElm.rightSibling == NULL) {
        node->nextElm.rightSibling = sibling;
    }
    else {
        setASTSibling(node->nextElm.rightSibling, sibling);
    }
}


void setASTparent(astNode *node, astNode *parent) {
    if (node != NULL) {
        node->nextElm.rightSibling = NULL;
        if (parent != NULL) {
            insertASTchild(parent, node);
        }
    }
}