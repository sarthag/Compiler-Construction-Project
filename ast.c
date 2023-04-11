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

// void populateLabels(){
//     token_key tk;
//     for(int i=0; i<NUM_OF_RELEVANT; i++){
//         tk = getTokenFromTTable(relevant[i], terminalHash);
//         labels[tk] = 1; 
//     }
// }

void createRelevant(){
    
    for(int i=0;i<NUM_OF_RELEVANT;i++){
        int index = getTokenFromTTable(needed[i], terminalHash);
        //printf("%d ", index);
        binRelevant[index]=1;
    }
}

astStack* initAST(){
    astStack* syntaxStack = (astStack*) malloc(sizeof(astStack));
    initASTStack(syntaxStack);
    createRelevant();
    syntaxTree = createSyntaxTree();
    astNodes = 0;
    return syntaxStack;
}



void topDownPass(astNode* parent, tree_node *parseNode, astStack* syntaxStack){
    if(parseNode==NULL){
        return;
    }
    if(parseNode->type == TERMINAL){
        printf("Terminal || Rule No: %d || lexeme %s\n", parseNode->rule, token_list[parseNode->element.t.tid]);
        if(binRelevant[parseNode->element.t.tid] == 1){
            astNode * new = createASTNode(parseNode->type, parseNode->rule, parseNode);
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
        printf("Non Terminal || Rule No: %d || NT Name: %s  ", parseNode->rule, nt_list[parseNode->element.nt.nid]);
        astNode* new = createASTNode(parseNode->type, parseNode->element.nt.nid, parseNode);
        astNode * temp;
        temp = parent->leftChild;
        // printf("Temp\n");
        if(temp == NULL){
            parent->leftChild = new;
            // printf("If Over\n");
        }
        else{
            while(temp->rightSibling != NULL){
                temp = temp->rightSibling;
            }
            temp->rightSibling = new;
        }
        // printf("Else Over\n");
        new->parent = parent;
        // printf("Parent Assigned\n");
        // printf("%d\n", syntaxStack->size);
        pushast(syntaxStack, new);
        // printf("Before Recursion\n");
        topDownPass(new, parseNode->left_child, syntaxStack);
    }
    topDownPass(parent, parseNode->right_sibling, syntaxStack);

    //check if it is a list node or if it is an irrelevant terminal - using a binary array for each of them 
    //set the rest of the attributes of temp - rule no, tree pointer, etc 
    
} 

void printASTstack(astStack * syntaxStack) {
    astStackNode * top = (astStackNode*)malloc(sizeof(astStackNode));
    top = syntaxStack -> top;
    while(top->next != NULL) {
        if (top->treeloc->nodeType == TERMINAL){
            printf("TERMINAL\t%s\tRule: %d\n", token_list[top->treeloc->name.t.tid], top->treeloc->rule_no);
        }
        else {
            printf("NON TERMINAL\t%s\tRule: %d\n", nt_list[top->treeloc->name.nt.nid], top->treeloc->rule_no);
        }
        top = top->next;

    }
}


astNode* findAction(astNode * current, astNode * prev, astNode * lastTerminal) {
    printf("current rule no: %d\n", current->rule_no);
    astNode * temp;
    astNode * par;
    switch (current->rule_no) {
    case 0:
        break;
    case 1:
        break;
    case 2:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 3:
        break;
    case 4:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 5:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 6:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        break;
    case 7:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 8:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 9:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 10:
        break;
    case 11: 
        temp = prev -> rightSibling;
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
        current->leftChild = prev->leftChild;
        break;
    case 14:
        temp = prev -> rightSibling;
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
        current->leftChild = prev->leftChild;
        break;
    case 17:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 18:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 19:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 20:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        break;
    case 21:
        temp = prev -> rightSibling;
        current->nodeType = temp->nodeType;
        current->name = temp->name;
        prev -> rightSibling = temp -> rightSibling;
        break;
    case 22:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 23:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 24:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        current->rightSibling = prev->rightSibling;
        break;
    case 25:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 26:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 27:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 28:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        current->rule_no = prev->rule_no;
        break;
    case 29:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 30:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 31:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 32:
        temp = prev -> rightSibling;
        current->nodeType = temp->nodeType;
        current->name = temp->name;
        prev -> rightSibling = temp -> rightSibling;
        break;
    case 33:
        temp = prev -> rightSibling;
        current->nodeType = temp->nodeType;
        current->name = temp->name;
        prev -> rightSibling = temp -> rightSibling;
        break;
    case 34:
        temp = prev -> rightSibling;
        current->nodeType = temp->nodeType;
        current->name = temp->name;
        prev -> rightSibling = temp -> rightSibling;
        break;
    case 35:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 36:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 37:
        break;
    case 38:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 39:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 40:
        temp = prev -> rightSibling;
        current->nodeType = temp->nodeType;
        current->name = temp->name;
        prev -> rightSibling = temp -> rightSibling;
    case 41:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 42:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        current->rule_no = prev->rule_no;
        break;
    case 43:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 44: 
        current->nodeType = prev->rightSibling->nodeType;
        current->name = prev->rightSibling->name;
        prev->rightSibling = prev->rightSibling->leftChild;
        break;
    case 45:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 46:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 47:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        break;
    case 48:
        temp = prev -> rightSibling;
        current->nodeType = temp->nodeType;
        current->name = temp->name;
        prev -> rightSibling = temp -> rightSibling;
        break;
    case 49:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        break;
    case 50:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 51:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 52:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 53:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 54:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 55:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 56:
        temp = prev->rightSibling;
        prev->leftChild = prev->rightSibling;
        prev->rightSibling = temp->rightSibling;
        temp->rightSibling = NULL;
        break;
    case 57:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 58:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 59:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 60:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        break;
    case 61:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        current->rightSibling = prev->rightSibling->rightSibling;
        prev->rightSibling->rightSibling = NULL;
        break;
    case 62:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 63:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 64:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 65:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 66:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 67:
        // current->nodeType = prev -> nodeType;
        // current->name = prev->name;
        // current->rightSibling = prev->rightSibling;
        break;
    case 68:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 69:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 70:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 71:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 72:
        break;
    case 73:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 74:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 75:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 76:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 77:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 78:
        if(prev->rightSibling->name.t.tid == EPSILON) {
            current->nodeType = prev->nodeType;
            current->name = prev->name;
            current->leftChild = prev->rightSibling;
        }
        break;
    case 79:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        current->rightSibling = prev->rightSibling->rightSibling;
        break;
    case 80:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        break;
    case 81:
        if(prev->rightSibling->name.t.tid == EPSILON) {
            current->nodeType = prev->nodeType;
            current->name = prev->name;
            current->leftChild = prev->rightSibling;
        }
        break;
    case 82:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        break;
    case 83:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 84:
        if(prev->rightSibling->name.t.tid == EPSILON) {
            current->nodeType = prev->nodeType;
            current->name = prev->name;
            current->leftChild = prev->rightSibling;
        }
        break;
    case 85:
        // printf("%d\n", prev->rightSibling == NULL);
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        current->rightSibling = prev->rightSibling->rightSibling;
        prev->rightSibling->rightSibling = NULL;
        break;
    case 86:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 87: 
        if(prev->rightSibling->name.t.tid == EPSILON) {
            current->nodeType = prev->nodeType;
            current->name = prev->name;
            current->leftChild = prev->rightSibling;
        }
        break;
    case 88:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        current->rightSibling = prev->rightSibling->rightSibling;
        prev->rightSibling->rightSibling = NULL;
        break;
    case 89:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 90:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 91:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 92:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 93:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 94:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        break;
    case 95:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 96:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 97:
        break;
    case 98:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        current->rightSibling = prev->rightSibling->rightSibling;
        prev->rightSibling->rightSibling = NULL;
        break;
    case 99:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 100:
        break;
    case 101:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        current->rightSibling = prev->rightSibling->rightSibling;
        prev->rightSibling->rightSibling = NULL;
        break;
    case 102:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 103:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 104:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 105:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 106:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 107:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 108:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 109:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 110:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 111:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        break;
    case 112:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 113:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 114:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 115:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 116:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 117:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 118:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 119:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 120:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 121:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 122:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 123:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
    case 124:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        break;
    case 125:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        temp = prev;
        while(temp->rightSibling->name.t.tid != CASE) {
            temp = temp->rightSibling;
        }
        current->rightSibling = temp->rightSibling;
        temp->rightSibling = NULL;
        break;
    case 126:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        temp = prev;
        while(temp->rightSibling->name.t.tid != CASE) {
            temp = temp->rightSibling;
        }
        current->rightSibling = temp->rightSibling;
        temp->rightSibling = NULL;
        break;
    case 127:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 128:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 129:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 130:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 131:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 132:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    case 133:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        break;
    case 134:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        break;
    case 135:
        current->nodeType = prev->rightSibling->nodeType;
        current->name = prev->rightSibling->name;
        prev->rightSibling = prev->rightSibling->rightSibling;
        break;
    case 136:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->rightSibling;
        break;
    case 137:
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        current->leftChild = prev->leftChild;
        break;
    default:
        // printf("Error: Rule No. invalid");
        // return NULL;
        break;
    }
    // free(prev);
    return current;
}

astNode* callfindAction(astNode* ASTroot, astStack* syntaxStack) {
    astNode * prev = popast(syntaxStack)->treeloc;
    printf("First rule: type: %d id: %s rule: %d\n",prev->nodeType, token_list[prev->name.t.tid], prev->rule_no);
    astNode * lastTerminal = prev;
    astNode * current = popast(syntaxStack)->treeloc;
    printf("First rule: type: %d id: %s rule: %d\n",current->nodeType, nt_list[current->name.nt.nid], current->rule_no);
    
    findAction(current, prev, lastTerminal);
    while(syntaxStack->top != NULL) {
        prev = current;
        current = popast(syntaxStack)->treeloc;
        // printf("First rule: type: %d id: %s rule: %d\n", current->nodeType, nt_list[current->name.nt.nid], current->rule_no);
        while(current->nodeType == TERMINAL) {
            prev = current;
            // printf("First rule: type: %d id: %s rule: %d\n", prev->nodeType, token_list[prev->name.t.tid], prev->rule_no);
            lastTerminal = current;
            current = popast(syntaxStack)->treeloc;
            // printf("First rule: type: %d id: %s rule: %d\n", current->nodeType, nt_list[current->name.nt.nid], current->rule_no);
        }
        if(prev->nodeType == TERMINAL) {
            printf("Prev: type: %d id: %s rule: %d\n", prev->nodeType, token_list[prev->name.t.tid], prev->rule_no);
        }
        else {
            printf("prev: type: %d id: %s rule: %d\n", prev->nodeType, nt_list[prev->name.nt.nid], prev->rule_no);
        }

        if(current->nodeType == TERMINAL) {
            printf("Current: type: %d id: %s rule: %d\n", current->nodeType, token_list[current->name.t.tid], current->rule_no);
        }
        else {
            printf("Current: type: %d id: %s rule: %d\n", current->nodeType, nt_list[current->name.nt.nid], current->rule_no);
        }
        findAction(current, prev, lastTerminal);
    }
}

// int main(){
//     astNodes = 0;
//     FILE* prog;
//     char* filename = "testOwn.txt";
//     char* parseTreeFile = "parseTree.txt";
//     // printf("read files\n");
//     removeComments(filename);
//     // printf("comments removed\n");
//     prog = readFile(filename);
//     // printf("file wo comments read\n");
//     populate_keyword_table();
//     printf("\n");
//     getNextToken(prog);
//     // printf("here\n");
//     InitializeParser();
//     // printf("here\n");
//     parse_code();
//     printf("parsing done\n");
//     //printParseTree(parseTree->root, parseTreeFile);   PRINT PARSE TREE HAS SEG FAULTS!!!!
//     printf("pt root: %s\n", nt_list[parseTree->root->element.nt.nid]);
//     syntaxStack = initAST();
//     printf("initAST()\n");
//     astNode* ASTroot = createASTNode(NON_TERMINAL, -1, parseTree->root);
//     printf("ast init \n");
//     topDownPass(ASTroot, parseTree->root, syntaxStack);    
//     printf("top down pass done\n");
//     printASTstack(syntaxStack);
//     printf("here\n");
//     callfindAction(ASTroot, syntaxStack);
//     printf("AST bottom up done");
//     // callfindAction(ASTroot, syntaxStack);
// }