// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------

#include "adt.h"

void initStack(stack* s) {
    s->top = NULL;
    s->size = 0; 
}

void *  makeElement(node_type type, int id){
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
    //free(top_node);
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
    new_node->rule = -1;
    new_node->parent = NULL;
    new_node->left_child = NULL;
    new_node->right_sibling = NULL;
    return new_node;
}

void insert_child(tree_node *parent, tree_node *child) {
    // insets the left child
    child->parent = parent;
    child->right_sibling = parent->left_child;
    parent->left_child = child; 
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
    //free(node);
}

void parse_tree_traversal(tree_node *node, FILE* fp) {
    if (node == NULL) {
        return;
    }
    if (node->type == NON_TERMINAL) {
        // printf("Non terminal\t");
        // non_terminal tok = node->element.nt;
        // printf("%d\n", node->element.nt.nid);
        if(node->element.nt.nid == program) {
            
            fprintf(stdout, "----- | Root Node (No Parent) | no | %s |%d |%d \n", nt_list[node->element.nt.nid] ,node -> rule,node ->type);
        }
        else {
            fprintf(stdout, "----- | %s | no | %s |%d|%d \n", nt_list[node->parent->element.nt.nid], nt_list[node->element.nt.nid],node ->rule, node ->type); // change this back
        }
    } 
    else {
        // printf("Terminal\t");
        token tok = node->element.t;
        if (tok.tid == NUM){
            fprintf(stdout, "| ----- | %d | %d | %s | %s | yes |%d|%d \n", tok.line_no, tok.num, token_list[tok.tid], nt_list[node->parent->element.nt.nid], node ->rule,node ->type);
        }
        else if (tok.tid == RNUM){
            fprintf(stdout, "| ---- | %d | %lf | %s | %s | yes |%d|%d \n", tok.line_no, tok.rnum, token_list[tok.tid], nt_list[node->parent->element.nt.nid],node ->rule,node ->type);
        }
        else if(tok.tid == EPSILON){
            fprintf(stdout, "| EPSILON | NA | %s | %s| yes |%d|%d \n",token_list[tok.tid], nt_list[node->parent->element.nt.nid],node ->rule,node ->type); // change this back

        }
        else{
            fprintf(stdout, "| %s | %d | %s | %s| yes |%d|%d \n", tok.lexeme, tok.line_no, token_list[tok.tid], nt_list[node->parent->element.nt.nid],node ->rule,node ->type); // change this back
        }
        
    }

    parse_tree_nodes++; 
    parse_tree_traversal(node->left_child, fp);
    parse_tree_traversal(node->right_sibling, fp);
}


void countPTNodes(tree_node *node) {
    if (node == NULL) {
        return;
    }
    
    parse_tree_nodes++; 
    countPTNodes(node->left_child);
    countPTNodes(node->right_sibling);
}