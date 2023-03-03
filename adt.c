#include "adt.h"
// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------

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
    // new_node -> treeLocation = treeLocation;
    s->top = new_node;
    s->size++;
    // printf("push exit\n");
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

void printStack(stack* s){
    printf("PRINTING STACK:\n");
    stack_node* current = s ->top; 
    while(current != NULL){
        if(current -> type == NON_TERMINAL){
            printf("NT: %d ->", current -> element.nt.nid);
        }
        else{
            printf("T: %d  -> ", current -> element.t.tid);
        }
        current = current -> next;
        
    }
    printf("NULL\n");

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

void inorder_traversal(tree_node *node, FILE* fp) {
    // printf("Inside inorder_traversal");
    if (node == NULL) {
        printf("Null node\n");
        return;
    }
    if (node->type == NON_TERMINAL) {
        printf("Non terminal\n");
        // non_terminal tok = node->element.nt;
        printf("%d\n", node->parent->element.nt.nid);
        if(node->element.nt.nid == 53) {
            printf("Here\n");
            printf("----- | Root Node (No Parent) | no | %d |\n", node->element.nt.nid);
        }
        printf("----- | %d | no | %d |\n", node->parent->element.nt.nid, node->element.nt.nid); // change this back
    } 
    else {
        printf("Terminal\n");
        token tok = node->element.t;
        if (tok.tid == NUM){
            fprintf(fp, "%s %s %s %s %s %s\n", "-----",tok.line_no, tok.num, tok.tid, node->parent->element.nt.nid, "yes");
        }
        else if (tok.tid == RNUM){
            fprintf(fp, "%s %s %s %s  %s\n", "-----", tok.line_no, tok.rnum, tok.tid, node->parent->element.nt.nid, "yes");
        }
        else{
            fprintf(fp, "%s %s %s %s  %s\n", tok.lexeme, tok.line_no, tok.tid, node->parent->element.nt.nid, "yes"); // change this back
        }
    }

    node->is_visited = 1;
    inorder_traversal(node->left_child, fp);
    inorder_traversal(node->right_sibling, fp);
}




// int main(){
//     parse_tree *pt = create_parse_tree();
//     non_terminal *nt = (non_terminal*)malloc(sizeof(struct nonTerminal));
//     nt->nid = 0;
//     tree_node* st = create_node(NON_TERMINAL, nt);
//     pt->root = st; 
//     token *t = (token*)malloc(sizeof(struct token));
//     t->tid = 1;
//     tree_node* t1 = create_node(TERMINAL, t);
//     insert_child(pt->root, t1);
//     token *tt = (token*)malloc(sizeof(struct token));
//     tt->tid = 2;
//     tree_node* t2 = create_node(TERMINAL, tt);
//     token *ttt = (token*)malloc(sizeof(struct token));
//     ttt->tid = 3;
//     tree_node* t3 = create_node(TERMINAL, ttt);
//     insert_child(pt->root->left_child, t3);
//     insert_child(pt->root, t2);

//     // printf("child1id: %d\n", pt->root->left_child->element.t.tid);
//     // printf("child2id: %d\n", pt->root->left_child->right_sibling->element.t.tid);
//     print_parse_tree(pt);

//     // stack_node* t1 = (stack_node*)malloc(sizeof(struct stack_node));
//     // t1 = pop(s);
//     // printf("Size: %d, popid: %d", s->size, t1->element.t.tid);
// }