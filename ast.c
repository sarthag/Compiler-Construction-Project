// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------

/*How to go about building an AST:
0)The AST node needs to be changed to include a list attribute which points to head of the list -> need to make a new structure called listhead
1)Top down apporoach creating a node and pushing it onto the stack
2)Bottom up approach has different categories for which we use the switch case
3)Each switch case will have the ast rules for that rule
4)Remember to malloc everything in step 1 so that we dont get bt with free
*/

// type - 0 is regNode, 1 is listHead, 2 is listElm

#include "ast.h"

void populateLabels(){
    token_key tk;
    for(int i=0; i<NUM_OF_RELEVANT; i++){
        tk = getTokenFromTTable(relevant[i], terminalHash);
        labels[tk] = 1; 
    }
}

void initAST(){
    astStack* syntaxStack = (astStack*) malloc(sizeof(astStack));
    initASTStack(syntaxStack);
    populateLabels();
    syntaxTree = createSyntaxTree();
    int rule = parseTree->root->rule;
    createAST(rule);
}

void createAST(int rule){
    switch (rule)
    {
    case 0:
        
        break;
    
    default:
        break;
    }
}

void createRelevant(){
    
    for(int i=0;i<NUM_OF_RELEVANT;i++){
        int index = getTokenFromKT(relevant[i], keyword_table);
        binRelevant[index]=1;
    }

}

void topDownPass(astNode* parent, tree_node *parseNode){

    if(parseNode==NULL){
        return;
    }
    if(parseNode->type == TERMINAL){
        if(binRelevant[parseNode->element.t.tid] == 1){
            astNode * new = createASTNode(parseNode->type, parseNode->rule, 0, parseNode);
            pushast(syntaxStack, parseNode);
        }
        
    }
    else if (parseNode->type == NON_TERMINAL){
        astNode* new = createASTNode(parseNode->type, parseNode->element.nt.nid, 0, parseNode);
        pushast(syntaxStack, parseNode);
        topDownPass(new, parseNode->left_child);
    }
    topDownPass(parent, parseNode->right_sibling);

    //check if it is a list node or if it is an irrelevant terminal - using a binary array for each of them 
    //set the rest of the attributes of temp - rule no, tree pointer, etc 
    
} 

void printASTstack(astStack * syntaxStack) {
    astStackNode * top = (astStackNode*)malloc(sizeof(astStackNode));
    top = syntaxStack -> top;
    while(top->next != NULL) {
        if (top->treeloc->type == TERMINAL){
            printf("TERMINAL\t%d\t%d\n", top->treeloc->element.t.tid, top->treeloc->rule);
        }
        else {
            printf("NON TERMINAL\t%d\t%d\n", top->treeloc->element.nt.nid, top->treeloc->rule);
        }

    }
}

int main(){
    initAST();
    astStackNode* ASTroot = createASTNode(NON_TERMINAL, -1, 0, parseTree->root);
    topDownPass(ASTroot, parseTree->root->left_child);
    printASTstack(syntaxStack);
}

astNode* findAction(astNode * current, astNode * prev){
    switch (current->rule_no)
    {
    case 0:

        break;
    case 1:

        break;
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;
    case 5:
    
        break;
    case 6:
        current->type.reg->leftChild = NULL;
        break;
    case 7:
    
        break;
    case 8:
    
        break;
    case 9:
    
        break;
    case 10:
    
        break;
    case 11:
    
        break;
    case 12:
    
        break;
    case 13:
    
        break;
    case 14:
    
        break;
    case 18:

        break;
    case 25:

        break;
    case 26:
        current->type.reg->leftChild = NULL;
        break;
    case 29:

    break;
    case 30:

        break;
    case 43:

        break;
    case 46:

        break;
    case 47:
        current = prev;
        break;
    case 68:
        current->rightSibling = current->pt->left_child->right_sibling;
        break;
    case 69:
        current->rightSibling = NULL;
        break;
    case 70:
        current = prev;
        break;
    case 78:
        current->type.reg->leftChild = prev;
        break;
    case 80:
        current->type.reg->leftChild = NULL;
        break;
    case 81:
        current->type.reg->leftChild = prev;
    case 83:
        current->type.reg->leftChild = NULL;
        break;
    case 84:
        current->type.reg->leftChild = prev;
    case 85:
        current->type.reg->leftChild = prev;
        break;
    case 86:
        current->type.reg->leftChild = NULL;
        break;
    case 87:
        current->type.reg->leftChild = prev;
        break;
    case 89:
        current->type.reg->leftChild = NULL;
        break;
    case 94:
        current->type.reg->leftChild = current->type.reg->leftChild->pt->left_child;
        current->type.reg->leftChild->rightSibling = prev;
        break;
    case 96:
        current->type.reg->leftChild = NULL;
        break;
    case 111:
        current = prev;
    case 124:

        break;

    default:
        printf("Error: Rule No. invalid");
        return NULL;
        break;
    }
    free(prev);
    return current;
}