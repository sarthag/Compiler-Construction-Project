#include "adt.h"


void initStack(stack* s) {
    s->top = NULL;
    s->size = 0; 
}


stack_node* create_stack_node(node_type type, void* element) {
    stack_node* new_node = (stack_node*) malloc(sizeof(stack_node));
    new_node->type = type;
    if (type == TERMINAL) {
        new_node->element.t = *(token*)element;
    } 
    
    else {
        new_node->element.nt = *(non_terminal*)element;
    }
    new_node->next = NULL;
    return new_node;
}


void push(stack* s, node_type type, void* element) {
    stack_node* new_node = create_stack_node(type, element);
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

tree_node *create_node(node_type type, void *element) {
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
        printf("%s", nts[node->element.nt.nid]); // change this back
    } else {
        printf("%s", terms[node->element.t.tid]); // change this back
    }
    node->is_visited = 1;
    inorder_traversal(node->left_child);
    inorder_traversal(node->right_sibling);
}


void print_parse_tree(parse_tree *tree) {
    inorder_traversal(tree->root);
    printf("\n");
}



int main(){
    stack *s = (stack*)malloc(sizeof(struct Stack));
    initStack(s);

    non_terminal *nt = (non_terminal*)malloc(sizeof(struct nonTerminal));
    nt->nid = 0;
    token *t = (token*)malloc(sizeof(struct token));
    t->tid = 69;


    push(s, NON_TERMINAL, nt);
    push(s, TERMINAL, t);
    printf("Size: %d, Topid: %d", s->size, s->top->element.t.tid);

    stack_node* t1 = (stack_node*)malloc(sizeof(struct stack_node));
    t1 = pop(s);
    printf("Size: %d, popid: %d", s->size, t1->element.t.tid);
}