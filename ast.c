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
        int index = getTokenFromTTable(relevant[i], terminalHash);
        //printf("%d ", index);
        binRelevant[index]=1;
    }
}

astStack* initAST(){
    astStack* syntaxStack = (astStack*) malloc(sizeof(astStack));
    printf("Stack made\n");
    initASTStack(syntaxStack);
    printf("initStack\n");
    //populateLabels();
    createRelevant();
    for(int i = 0; i < NUM_OF_RELEVANT; i++) {
        printf("%d ", binRelevant[i]);
    }
    syntaxTree = createSyntaxTree();
    printf("\nSyntax tree created\n");
    // int rule = parseTree->root->rule;
    // createAST(rule);
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
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 3:
        break;
    case 4:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 5:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 6:
        par = current->parent;
        current->parent->leftChild = prev;
        current->rightSibling = NULL;
        current->leftChild = prev->rightSibling;
        current->parent = par;
        break;
    case 7:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 8:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 9:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 10:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 11: 
        temp = prev -> rightSibling;
        prev->rightSibling = temp->rightSibling;
        prev->leftChild = temp;
        break;
    case 12:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->rightSibling = prev->rightSibling->rightSibling;
        current->leftChild = prev->rightSibling;
        break;
    case 13:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 14:
        temp = prev -> rightSibling;
        prev->rightSibling = temp->rightSibling;
        prev->leftChild = temp;
        break;
    case 15:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->rightSibling = prev->rightSibling->rightSibling;
        current->leftChild = prev->rightSibling;
        break;
    case 16: 
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 17:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 18:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 19:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 20:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->rightSibling = NULL;
        current -> leftChild = prev -> rightSibling;
        break;
    case 21:
        temp = prev -> rightSibling;
        current->nodeType = temp->nodeType;
        current->name = temp->name;
        prev -> rightSibling = temp -> rightSibling;
        break;
    case 22:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 23:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 24:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 25:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 26:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 27:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 28:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 29:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 30:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 31:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 32:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current -> leftChild = prev -> rightSibling;
        current->rightSibling = NULL;
        break;
    case 33:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->leftChild = prev->rightSibling;
        current->rightSibling = NULL;
        break;
    case 34:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->leftChild = prev->rightSibling;
        current->rightSibling = NULL;
        break;
    case 35:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 36:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 37:
        break;
    case 38:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 39:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 40:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->leftChild = prev->rightSibling;
        current->rightSibling = NULL;
    case 41:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 42:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 43:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 44: 
        par = current->parent;
        current->parent->leftChild = prev->rightSibling;
        prev->rightSibling = current->leftChild;
        current->leftChild = prev;
        prev->leftChild = prev->rightSibling;
        prev->rightSibling = prev->rightSibling->rightSibling;
        break;
    case 45:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 46:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 47:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->leftChild = prev->rightSibling;
        current->rightSibling = NULL;
        break;
    case 48:
        par = current->parent;
        current->parent->leftChild = prev->rightSibling;
        current->parent = par;
        current->leftChild = prev;
        prev->rightSibling = current->rightSibling;
        current->rightSibling = NULL;
        break;
    case 49:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->leftChild = prev->rightSibling;
        current->rightSibling = NULL;
        break;
    case 50:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 51:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 52:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 53:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 54:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 55:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 56:
        temp = prev->rightSibling;
        prev->leftChild = prev->rightSibling;
        prev->rightSibling = temp->rightSibling;
        break;
    case 57:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 58:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 59:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 60:
        prev->leftChild = prev->rightSibling;
        prev->rightSibling = NULL;
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 61:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->leftChild = prev->rightSibling;
        current->rightSibling = NULL;
        break;
    case 62:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 63:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 64:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 65:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 66:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 67:
        // current->nodeType = prev -> nodeType;
        // current->name = prev->name;
        // current->rightSibling = prev->rightSibling;
        break;
    case 68:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 69:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 70:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 71:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 72:
        break;
    case 73:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 74:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 75:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 76:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 77:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 78:
        current->leftChild = prev;
        break;
    case 79:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->leftChild = prev->rightSibling;
        current->rightSibling = current->leftChild->rightSibling;
        current->leftChild->rightSibling = NULL;
        break;
    case 80:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 81:
        
        break;
    case 82:
        
        break;
    case 83:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 84:
        
        break;
    case 85:
        prev->leftChild = prev->rightSibling->leftChild;
        prev->rightSibling = prev->rightSibling->rightSibling;
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 86:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 87:
        printf("%s\n", nt_list[current->name.nt.nid]);
        printf("%s\n", token_list[prev->name.t.tid]);
        printf("%s\n", token_list[prev->rightSibling->name.t.tid]);
        if(prev->rightSibling->name.t.tid == EPSILON) {
            printf("here\n");
            current->nodeType = prev->nodeType;
            current->name = prev->name;
            current->leftChild = NULL;
        }
        printf("%s\n", token_list[current->name.t.tid]);
        break;
    case 88:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->leftChild = prev->rightSibling;
        current->rightSibling = current->leftChild->rightSibling;
        current->leftChild->rightSibling = NULL; 
        break;
    case 89:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 90:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 91:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 92:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 93:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 94:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->leftChild = prev->rightSibling;
        current->rightSibling = NULL;
        break;
    case 95:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 96:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 97:
        break;
    case 98:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->leftChild = prev->rightSibling;
        current->rightSibling = NULL;
        break;
    case 99:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 100:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->leftChild = prev->rightSibling;
        current -> rightSibling = current->leftChild->rightSibling;
        current->leftChild->rightSibling = NULL;
        break;
    case 101:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->leftChild = prev->rightSibling;
        current->rightSibling = NULL;
        break;
    case 102:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 103:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 104:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 105:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 106:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 107:
        break;
    case 108:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 109:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 110:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 111:
        printf("%s\n", nt_list[current->name.nt.nid]);
        current->nodeType = prev->nodeType;
        current->name = prev->name;
        printf("%s\n", token_list[current->name.t.tid]);
        break;
    case 112:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 113:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 114:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 115:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 116:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 117:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 118:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 119:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 120:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 121:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 122:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 123:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->leftChild = prev->rightSibling;
        current->rightSibling = NULL;
    case 124:
        break;
    case 125:
        temp = prev->rightSibling;
        prev->leftChild = prev->rightSibling;
        while(temp->rightSibling->name.t.tid != CASE) {
            temp = temp->rightSibling;
        }
        prev->rightSibling = temp->rightSibling;
        temp->rightSibling = NULL;
        break;
    case 126:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 127:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 128:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 129:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 130:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 131:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 132:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    case 133:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->leftChild = prev->rightSibling;
        current->rightSibling = NULL;
        break;
    case 134:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->leftChild = prev->rightSibling;
        current->rightSibling = NULL;
        break;
    case 135:
        temp = prev->rightSibling;
        par = current->parent;
        current->parent->leftChild = temp;
        current->parent = par;
        prev->rightSibling = temp->rightSibling;
        current->rightSibling = NULL;
        current->leftChild = prev;
        // prev = temp;
        break;
    case 136:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        current->leftChild = prev->rightSibling;
        current->rightSibling = NULL;
        break;
    case 137:
        par = current->parent;
        current->parent->leftChild = prev;
        current->parent = par;
        break;
    default:
        // printf("Error: Rule No. invalid");
        // return NULL;
        break;
    }
    free(prev);
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

int main(){
    astNodes = 0;
    FILE* prog;
    char* filename = "testOwn.txt";
    char* parseTreeFile = "parseTree.txt";
    // printf("read files\n");
    removeComments(filename);
    // printf("comments removed\n");
    prog = readFile(filename);
    // printf("file wo comments read\n");
    populate_keyword_table();
    printf("\n");
    getNextToken(prog);
    // printf("here\n");
    InitializeParser();
    // printf("here\n");
    parse_code();
    printf("parsing done\n");
    //printParseTree(parseTree->root, parseTreeFile);   PRINT PARSE TREE HAS SEG FAULTS!!!!
    printf("pt root: %s\n", nt_list[parseTree->root->element.nt.nid]);
    syntaxStack = initAST();
    printf("initAST()\n");
    astNode* ASTroot = createASTNode(NON_TERMINAL, -1, parseTree->root);
    printf("ast init \n");
    topDownPass(ASTroot, parseTree->root, syntaxStack);    
    printf("top down pass done\n");
    printASTstack(syntaxStack);
    printf("here\n");
    callfindAction(ASTroot, syntaxStack);
    printf("AST bottom up done");
    // callfindAction(ASTroot, syntaxStack);
}