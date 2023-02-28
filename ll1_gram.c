#include "ll1_gram.h"

char *non_terminals[]={"start", "module", "otherModules", "moduleDef"};
char *terminals[]={"NUM", "ID", "COLON", "EPSILON"};

int get_id(char *str, int t){
    //printf("call to get id ");
    //t= 0 for non terminal and 1 and terminal
    //the id for epsilong is -1
    //id returned is -2 if it isn't detected 
    if(strcmp(str, "epsilon")==0){
        return -1;
    }
    if(t==0){
        for(int i=0;i< NUM_OF_NONTERMINALS; i++ ){
            if(strcmp(non_terminals[i], str)==0){
                //printf("strcmp value %d ", strcmp(non_terminals[i], str));
                //printf("%s \n", non_terminals[i]);
                return i;
            }
        //printf("%s non_terminal : Symbol doesn't exist %s \n", str, non_terminals[i]);
        }
    }
    else {
        for(int i=0;i< NUM_OF_TERMINALS; i++ ){
        if(strcmp(terminals[i], str)==0){
            return i;
        }
        //printf("%s terminal : Symbol doesn't exist %s \n", str, terminals[i]);
    }
    }
    printf("not detected \n");
    return -2;
    
}


bool isTerm(char* str){
    if(str[0] >= 65 && str[0]<= 90){
        return 1;
    }
    else if(str[0]>=97 && str[0]<=122){
        return 0;
    }
    return -1;
}


void generateGrammar(){
    FILE *fp = fopen("grammar_fake.txt", "r");
    if(fp ==NULL){
        printf("Error in opening the file ");
    }
    char lineBuf[MAX_LINE_LENGTH];
    int rule_no = 0;
    
    while(fgets(lineBuf, sizeof(lineBuf), fp)!=NULL ){
        char *str;
        rhs *firstRHS = NULL;
        rhs *prev_rhs = NULL;

        str=strtok(lineBuf, " \n");
        for(int i = 0; str != NULL; i++){
            if(i==0){
                //lhs
                G[rule_no].lhs_id = get_id(str, 0);
                G[rule_no].firstRHS = NULL;   
            }
            else {
                rhs *new_rhs = (rhs *)malloc(sizeof(rhs));
                new_rhs->isTerminal = isTerm(str);
                new_rhs->rhs_id = get_id(str, new_rhs->isTerminal);
                new_rhs->nextRHS = NULL;
                
                if(prev_rhs==NULL){
                    //first rule of rhs 
                    firstRHS = new_rhs;
                }
                else{
                    //other rules of rhs
                    prev_rhs->nextRHS = new_rhs;
                }
                
                new_rhs->prevRHS = prev_rhs;
                prev_rhs = new_rhs;
                
            }
            str=strtok(NULL, " \n");
        }
        G[rule_no].firstRHS = firstRHS;
        G[rule_no].lastRHS = prev_rhs;
        rule_no++;
    }


}

int main(){
    //lhs G1[NUM_OF_RULES];
    //G1= generateGrammar();
    generateGrammar();
    for(int i=0;i<NUM_OF_RULES;i++){
        printf("LHS_ID %d ", G[i].lhs_id);
        // printf("Tail: %d", G[i].lastRHS->rhs_id);
        rhs *temp = G[i].lastRHS;
        while(temp != NULL){
            printf("RHS_ID %d ", temp->rhs_id);
            temp=temp->prevRHS;
        }
        printf("\n");
        
    }
    return 0;
}


