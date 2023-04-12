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
    new -> rule_no = pTNode->rule; 
    printf("\n%d\t%d\t%d\n", rule_no, new->rule_no, pTNode->rule);
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

void ast_traversal(astNode *node) {
    if (node == NULL) {
        return;
    }
    if (node->nodeType == NON_TERMINAL) {
        // printf("Non terminal\t");
        // non_terminal tok = node->element.nt;
        // printf("%d\n", node->element.nt.nid);
        if(node->name.nt.nid == program) {
            printf("Node: %s | Rule: %d | Type: NON TERMINAL\n", nt_list[node->name.nt.nid], node->rule_no);
            // fprintf(stdout, "----- | Root Node (No Parent) | no | %s |%d |%d \n", nt_list[node->name.nt.nid] ,node->rule_no,node ->nodeType);
        }
        else {
            printf("Node: %s | Rule: %d | Type: NON TERMINAL\n", nt_list[node->name.nt.nid], node->rule_no);
            // fprintf(stdout, "----- | %s | no | %s |%d|%d \n", nt_list[node->parent->name.nt.nid], nt_list[node->name.nt.nid],node ->rule_no, node ->nodeType); // change this back
        }
    } 
    else if (node->nodeType == TERMINAL) {
        // printf("Terminal\t");
        token tok = node->name.t;
        if (tok.tid == NUM){
            printf("Node: %s | Lexeme: %d | Rule: %d | Type: TERMINAL\n", token_list[node->name.nt.nid], node->pt->element.t.num, node->rule_no);
            // fprintf(stdout, "| ----- | %d | %d | %s | %s | yes |%d|%d \n", tok.line_no, tok.num, token_list[tok.tid], nt_list[node->parent->name.nt.nid], node ->rule_no,node ->nodeType);
        }
        else if (tok.tid == RNUM){
            printf("Node: %s | Lexeme: %f | Rule: %d | Type: TERMINAL\n", token_list[node->name.nt.nid], node->pt->element.t.rnum, node->rule_no);
            // fprintf(stdout, "| ---- | %d | %f | %s | %s | yes |%d|%d \n", tok.line_no, tok.rnum, token_list[tok.tid], nt_list[node->parent->name.nt.nid],node ->rule_no, node ->nodeType);
        }
        else if(tok.tid == EPSILON){
            astNodes--;
            // printf("Node: %s | Lexeme: EPSILON | Rule: %d | Type: TERMINAL\n", token_list[node->name.nt.nid], node->rule_no);
            // fprintf(stdout, "| EPSILON | NA | %s | %s| yes |%d|%d \n",token_list[tok.tid], nt_list[node->parent->name.nt.nid],node ->rule_no, node ->nodeType); // change this back

        }
        else{
            printf("Node: %s | Lexeme: %s | Rule: %d | Type: TERMINAL\n", token_list[node->name.nt.nid], node->pt->element.t.lexeme, node->rule_no);
            // fprintf(stdout, "| %s | %d | %s | %s| yes |%d|%d \n", node->pt->element.t.lexeme, tok.line_no, token_list[tok.tid], nt_list[node->parent->name.nt.nid], node ->rule_no, node ->nodeType); // change this back
        }
    }

    // if(node->type==0 && node->rule==-1){
    //     printf("\nThe non terminal is %d \n", node->element.nt.nid);
    // }
    // printf("Here\n");
    astNodes++; 
    // printf("Here\n");
    ast_traversal(node->leftChild);
    ast_traversal(node->rightSibling);
}

void countASTNodes(astNode* node) {
    if (node == NULL) {
        return;
    }
    if (node->nodeType == TERMINAL && node->name.t.tid == EPSILON) {
        astNodes--;
    }
    astNodes++; 
    countASTNodes(node->leftChild);
    countASTNodes(node->rightSibling);
}