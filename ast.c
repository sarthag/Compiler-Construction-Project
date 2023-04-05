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