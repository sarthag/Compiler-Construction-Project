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
    for(int i=0; i<NUM_OF_RELAVENT; i++){
        tk = getTokenFromTTable(relavent[i], terminalHash);
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

astNode* topDownPass(astNode* parent, tree_node *parseNode){

    if(parseNode==NULL){
        return;
    }
    if(parseNode->type == TERMINAL){
        if(binRelevant[parseNode->element.t.tid] == 1){
            createASTNode(parseNode->type, parseNode->rule, ,parseNode)
        }
    }


    //check if it is a list node or if it is an irrelevant terminal - using a binary array for each of them 
    //set the rest of the attributes of temp - rule no, tree pointer, etc 
    
} 

int main(){

}