#include "astadt.h"

void initASTStack(astStack* s) {
    s->top = NULL;
    s->size = 0; 
}

astStackNode* createastStackNode(astNode *treeloc){
    // printf("Creating ast Stack Node\n");
    astStackNode* new = (astStackNode*) malloc(sizeof(astStackNode));
    // printf("mallocd\n");
    new -> treeloc = treeloc;
    // printf("treeloc assigned\n");
    new -> next = NULL;

    return new; 
}

void pushast(astStack* s, astNode *treeloc){
    // printf("Inside pushast\n");
    astStackNode* node = createastStackNode(treeloc);
    // printf("Stack Node Created\n");
    printf("%d\n", s->size);
    s->size++;
    // printf("size++\n");
    node->next = s->top; 
    // printf("node next\n");
    s->top = node;
    // printf("s top done\n");
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

astNode* createASTNode(node_type nodeType,int rule_no,tree_node* pTNode){
    astNode *new = (astNode*) malloc(sizeof(astNode));
    new -> rule_no = rule_no; 
    // new-> typeId = typeID;
    new -> pt = pTNode;
    if(pTNode -> type == TERMINAL){
        new -> nodeType = TERMINAL;
        new -> name.t.tid = pTNode ->element.t.tid;

    }
    else if(pTNode -> type == NON_TERMINAL){
        new -> nodeType = NON_TERMINAL;
        new -> name.nt.nid = pTNode -> element.nt.nid;
    }
    new->parent = NULL;
    new->leftChild = NULL;

    return new; 
}
void deleteASTnode(astNode * node){
    astNode * parent = node->parent;
    astNode * prev = NULL;
    astNode * temp = parent->leftChild;
    if(node->name.t.tid != temp->name.t.tid){

    }
    else{
        while(node->name.t.tid != temp->name.t.tid){
            prev = temp;
            temp = temp->rightSibling;
        }
        prev->rightSibling = temp->rightSibling;
    }
    free(node);
    
}

// void insertASTchild(astNode *parent, astNode* child, int parentType){
//     child -> parent = parent; 

//     switch (parentType)
//     {
//     case 0:
//         if(parent->leftChild == NULL){
//             parent->leftChild = child;
//         }
//         else{
//             astNode *temp = parent->leftChild;
//             while(temp->rightSibling != NULL){
//                 temp = temp->rightSibling;
//             }
//             temp->rightSibling = child;
//         }
//         break;
//     case 1:
//         if (parent->leftChild == NULL){
//             parent->leftChild = child;
//         }
//         else{
//             astNode *temp = parent->leftChild;
//             while(temp->rightSibling != NULL){
//                 temp = temp->rightSibling;
//             }
//             temp->rightSibling = child;
//         }
//     default:
//         printf("error: parent invalid");
//         break;
//     }
// }


// void setASTSibling(astNode *node, astNode *sibling) {
//     sibling->parent = node->parent;
//     if (node->rightSibling == NULL) {
//         node->rightSibling = sibling;
//     }
//     else {
//         setASTSibling(node->rightSibling, sibling);
//     }
// }


// void setASTparent(astNode *node, astNode *parent) {
//     if (node != NULL) {
//         node->rightSibling = NULL;
//         if (parent != NULL) {
//             insertASTchild(parent, node, parent->typeId);
//         }
//     }
// }