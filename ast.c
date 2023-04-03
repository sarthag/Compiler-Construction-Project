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
#include "ast.h"

void initAST(){
    astStack* syntaxStack = (astStack*) malloc(sizeof(astStack));
    initASTStack(syntaxStack);
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

astNode* topDownPass(astNode* parent, tree_node *root){
    if(root==NULL){
        return;
    }
    astNode* temp = (astNode*)malloc(sizeof(astNode));
    //check if it is a list node or if it is an irrelevant terminal - using a binary array for each of them 

    //set the rest of the attributes of temp - rule no, tree pointer, etc 
    temp->parent=parent;
    temp->child.leftChild= topDownPass(temp, root->left_child);
    tree_node* temp1= root->left_child;
    astNode* nextChild= temp->child.leftChild;
    while(temp1->right_sibling!=NULL){
        temp1=temp1->right_sibling;
        nextChild->sibast= topDownPass(temp, temp1);
    }
    if(root == parseTree-> root){
        syntaxTree->root = temp;
    }
} 

int main(){

}