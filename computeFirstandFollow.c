#include "ll1_gram.c"

void findFirst(lhs target, bool First[][NUM_OF_TERMINALS], bool firstDone[]){
    rhs *temp = target.firstRHS;
    if (temp->isTerminal == 1){
        if(temp->rhs_id == NUM_OF_TERMINALS - 1){          // assuming EPSILON id = 3
            rhs* temp2 = temp->nextRHS;
            if(temp2 != NULL){           
            int i = 0;
            for(i; i < NUM_OF_RULES; i++){
                if(G[i].lhs_id == temp2->rhs_id){
                    break;
                }
            }
            
            findFirst(G[i], First, firstDone);
            for(int i = 0; i < NUM_OF_TERMINALS; i++){
                if (First[temp->rhs_id][i] == 1)
                First[target.lhs_id][i] = First[temp->rhs_id][i];
                firstDone[target.lhs_id] = 1;
            }
            }
        }
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
            if(First[temp->rhs_id][i] == 1)
            First[target.lhs_id][i] = First[temp->rhs_id][i];
            firstDone[target.lhs_id] = 1;
        }
    }
}

void findFollow(lhs start, rhs *target, rhs *temp, bool Follow[][NUM_OF_TERMINALS]){
    if (target->isTerminal == 1){
        return;
    }
    if(temp == NULL){
        for(int i =0; i < NUM_OF_TERMINALS; i++){
            Follow[target->rhs_id][i] = Follow[start.lhs_id][i];
        }
        return; 
    }
    if (temp->isTerminal == 1){
        Follow[target->rhs_id][temp->rhs_id] = 1;
        return;
    }
    for(int i =0; i < NUM_OF_TERMINALS - 1; i++){
        if (First[temp->rhs_id][i] == 1){
            Follow[target->rhs_id][i] = First[temp->rhs_id][i];
        }
    }
    if(First[temp->rhs_id][NUM_OF_TERMINALS - 1] == 0){
        return;
    }
    rhs *temp2 = temp->nextRHS;
    if(temp2 == NULL){
        for(int i =0; i < NUM_OF_TERMINALS; i++){
            if (Follow[start.lhs_id][i] == 1)
            Follow[target->rhs_id][i] = Follow[start.lhs_id][i];
        }
        return; 
    }
    findFollow(start, target, temp2, Follow);

}


void computeFirstandFollow (){
    //lhs G1[NUM_OF_RULES];
    //G1= generateGrammar();
    generateGrammar();

    for(int j = NUM_OF_RULES - 1; j >= 0; j--){
        findFirst(G[j], First, firstDone);
    }

    for (int j = 0; j < 4; j++){
        printf("\n%d\n%d\n", j, firstDone[j]);

        for(int i = 0; i < NUM_OF_TERMINALS; i++){
            printf("%d", First[j][i]);
        }
    }

    Follow[0][NUM_OF_TERMINALS - 1] = 1;

    for(int j = 0; j < NUM_OF_RULES; j++){
        rhs * target = G[j].firstRHS;
        while (target != NULL)
        {
            rhs * temp = target->nextRHS;
            findFollow(G[j], target, temp, Follow); 
            target = temp;
        }       
    }

    for (int j = 0; j < NUM_OF_NONTERMINALS; j++){
        printf("\n");
        for(int i = 0; i < NUM_OF_TERMINALS; i++){
            
            printf("%d", Follow[j][i]);
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