#include "ll1_gram.c"

void findFirst(lhs target, bool First[][NUM_OF_TERMINALS], bool firstDone[]){
    rhs *temp= target.firstRHS;
    if (temp->isTerminal == 1){
        First[target.lhs_id][temp->rhs_id] = 1;
        firstDone[target.lhs_id] = 1;
    }
    else{
        if (firstDone[temp->rhs_id] == 0){
            int i = 0;
            for(i; i < NUM_OF_RULES; i++){
                if(G[i].lhs_id == temp->rhs_id){
                    break;
                }
            }
            
            findFirst(G[i], First, firstDone);
        }
        for(int i = 0; i < NUM_OF_TERMINALS; i++){
            First[target.lhs_id][i] = First[temp->rhs_id][i];
            firstDone[target.lhs_id] = 1;
        }
    }
}
int main(){
    //lhs G1[NUM_OF_RULES];
    //G1= generateGrammar();
    generateGrammar();
    bool First[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
    bool firstDone[NO_NON_TERMINALS];

    for(int j = NUM_OF_RULES - 3; j >= 0; j--){
        findFirst(G[j], First, firstDone);
    }

    for (int j = 0; j < 4; j++){
        printf("\n%d\n%d\n", j, firstDone[j]);

        for(int i = 0; i < NO_TERMINALS; i++){
            printf("%d", First[4][i]);
        }
    }
    return 0;
}
/*
int main(){
    bool First[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
    bool firstDone[NO_NON_TERMINALS];

    for (int j = 0; j < 5; j++){
        findFirst(G[j], First, firstDone);
    }
    for(int i = 0; i < NO_TERMINALS; i++){
        printf("%d ", First[0][i]);
    }
}
*/