// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------

/*How to go about building an AST:
1.Pick the node
2. Do something
3. Push its children on the stack
4. Do something*/
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
