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
            astNode * temp;
            temp = parent -> leftChild;
            if(temp == NULL){
                parent->leftChild = new;
            }
            else{
                while(temp->rightSibling != NULL){
                    temp = temp->rightSibling;
                }
                temp->rightSibling = new;
            }
            new->parent = parent;
            pushast(syntaxStack, new);
        }
        
    }
    else if (parseNode->type == NON_TERMINAL){
        astNode* new = createASTNode(parseNode->type, parseNode->element.nt.nid, 0, parseNode);
        astNode * temp;
        temp = parent->leftChild;
        if(temp == NULL){
            parent->leftChild = new;
        }
        else{
            while(temp->rightSibling != NULL){
                temp = temp->rightSibling;
            }
            temp->rightSibling = new;
        }
        new->parent = parent;
        pushast(syntaxStack, new);
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
    astNode* ASTroot = createASTNode(NON_TERMINAL, -1, 0, parseTree->root);
    topDownPass(ASTroot, parseTree->root->left_child);    
    printASTstack(syntaxStack);
    callfindAction(ASTroot);
}

astNode* findAction(astNode * current, astNode * prev, astNode * lastTerminal) {
    switch (current->rule_no) {
    case 0:
        break;
    case 1:
        break;
    case 2:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 3:

        break;
    case 4:

        break;
    case 5:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 6:
        
        break;
    case 7:
    
        break;
    case 8:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 9:
    
        break;
    case 10:
    
        break;
    case 11:
        astNode * temp = prev -> rightSibling;
        prev->rightSibling = temp->rightSibling;
        prev->leftChild = temp;
        break;
    case 12:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->rightSibling = prev->rightSibling->rightSibling;
        current->leftChild = prev->rightSibling;
        break;
    case 13:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 14:
        astNode * temp = prev -> rightSibling;
        prev->rightSibling = temp->rightSibling;
        prev->leftChild = temp;
        break;
    case 15:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->rightSibling = prev->rightSibling->rightSibling;
        current->leftChild = prev->rightSibling;
        break;
    case 16: 
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 17:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 18:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 19:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 22:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 23:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 24:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 25:
        current->nodeType = prev -> nodeType;
        current->name = prev->name;
        current->rightSibling = prev->rightSibling;
        break;
    case 26:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 27:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 28:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 29:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 30:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 31:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 32:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 35:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 36:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 38:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 39:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 41:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 42:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 43:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 45:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 46:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 50:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 51:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 52:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 53:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 54:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 57:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 58:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 59:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 62:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 63:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 64:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 65:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 66:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 67:
        // current->nodeType = prev -> nodeType;
        // current->name = prev->name;
        // current->rightSibling = prev->rightSibling;
        break;
    case 68:
        current->nodeType = prev -> nodeType;
        current->name = prev->name;
        current->rightSibling = prev->rightSibling;
        break;
    case 69:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 70:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 71:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 75:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 76:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 77:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    
    case 78:
        current->leftChild = prev;
        break;
    case 80:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 81:
        
        break;
    case 83:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 84:
        
        break;
    case 85:
        
        break;
    case 86:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 87:
        current->leftChild = lastTerminal;
        current->leftChild->rightSibling = prev;
        break;
    case 89:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 91:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 92:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 93:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 94:
        current->leftChild = lastTerminal;
        current->leftChild->rightSibling = prev;
        break;
    case 95:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 96:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 99:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 102:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 103:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 104:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 105:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 106:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 108:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 109:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 111:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 112:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 113:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 114:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 115:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 116:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 117:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 118:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 119:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 120:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 121:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 122:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 123:
        current -> nodeType = prev -> nodeType
        current ->name = prev->name
        current->leftChild = prev->rightSibling
    case 124:

        break;
    case 127:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 128:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 129:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 130:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 131:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 132:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 137:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    default:
        printf("Error: Rule No. invalid");
        return NULL;
        break;
    }
    free(prev);
    return current;
}

astNode* callfindAction(astNode* ASTroot, astStack* syntaxStack) {
    astNode * prev = popast(syntaxStack);
    astNode * lastTerminal = prev;
    astNode * current = popast(syntaxStack);
    findAction(current, prev, lastTerminal);
    while(syntaxStack->top != NULL) {
        current = popast(syntaxStack);
        if(current->nodeType == TERMINAL) {
            prev = current;
            lastTerminal = current;
            current = popast;
        }
        findAction(current, prev, lastTerminal);
    }
}