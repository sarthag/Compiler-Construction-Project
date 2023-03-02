#include "computeFirstandFollow.h"

// void findf1(lhs target){
//     printf("here %d\n", target.lhs_id);
//     rhs *temp = target.f1RHS;
//     if (temp->isTerminal == 1){
//         if(temp->rhs_id == NUM_OF_TERMINALS - 1){          // assuming EPSILON id = 3
//         if(temp->rhs_id == NUM_OF_TERMINALS - 1){      
//             rhs* temp2 = temp->nextRHS;
//             if(temp2 != NULL){           
//             int i = 0;
//             for(i; i < NUM_OF_RULES; i++){
//                 if(G[i].lhs_id == temp2->rhs_id){
//                     break;
//                 }
//             }
            
//             findf1(G[i]);
//             for(int i = 0; i < NUM_OF_TERMINALS; i++){
//                 if (f1[temp->rhs_id][i] == 1)
//                 f1[target.lhs_id][i] = f1[temp->rhs_id][i];
//                 f1Done[target.lhs_id] = 1;
//             }
//             }
//         }
//         f1[target.lhs_id][temp->rhs_id] = 1;
//         f1Done[target.lhs_id] = 1;
//     }
//     else{
//         if (f1Done[temp->rhs_id] == 0){
//             int i = 0;
//             for(i; i < NUM_OF_RULES; i++){
//                 if(G[i].lhs_id == temp->rhs_id){
//                     break;
//                 }
//             }
            
//             findf1(G[i]);
//         }
//         for(int i = 0; i < NUM_OF_TERMINALS; i++){
//             if(f1[temp->rhs_id][i] == 1)
//             f1[target.lhs_id][i] = f1[temp->rhs_id][i];
//             f1Done[target.lhs_id] = 1;
//         }
//     }
// }

// void findf2(lhs start, rhs *target, rhs *temp){
//     if (target->isTerminal == 1){
//         return;
//     }
//     if(temp == NULL){
//         for(int i =0; i < NUM_OF_TERMINALS; i++){
//             f2[target->rhs_id][i] = f2[start.lhs_id][i];
//         }
//         return; 
//     }
//     if (temp->isTerminal == 1){
//         f2[target->rhs_id][temp->rhs_id] = 1;
//         return;
//     }
//     for(int i =0; i < NUM_OF_TERMINALS - 1; i++){
//         if (f1[temp->rhs_id][i] == 1){
//             f2[target->rhs_id][i] = f1[temp->rhs_id][i];
//         }
//     }
//     if(f1[temp->rhs_id][NUM_OF_TERMINALS - 1] == 0){
//         return;
//     }
//     rhs *temp2 = temp->nextRHS;
//     if(temp2 == NULL){
//         for(int i =0; i < NUM_OF_TERMINALS; i++){
//             if (f2[start.lhs_id][i] == 1)
//             f2[target->rhs_id][i] = f2[start.lhs_id][i];
//         }
//         return; 
//     }
//     findf2(start, target, temp2);

// }


// void computef1andf2(){
//     //lhs G1[NUM_OF_RULES];
//     //G1= generateGrammar();
//     for(int j = NUM_OF_RULES - 1; j >= 0; j--){
//         findf1(G[j]);
//     }

//     for (int j = 0; j < NUM_OF_NONTERMINALS; j++){
//         printf("\n%d\n%d\n", j, f1Done[j]);

//         for(int i = 0; i < NUM_OF_TERMINALS; i++){
//             printf("%d", f1[j][i]);
//         }
//     }

//     f2[0][NUM_OF_TERMINALS - 1] = 1;

//     for(int j = 0; j < NUM_OF_RULES; j++){
//         rhs * target = G[j].f1RHS;
//         while (target != NULL)
//         {
//             rhs * temp = target->nextRHS;
//             findf2(G[j], target, temp); 
//             target = temp;
//         }       
//     }

//     for (int j = 0; j < NUM_OF_NONTERMINALS; j++){
//         printf("\n");
//         for(int i = 0; i < NUM_OF_TERMINALS; i++){
            
//             printf("%d", f2[j][i]);
//         }      
//     }
// }

// void syncronization_set(){
//     token_key semicol = SEMICOL, bc = BC, sqbc = SQBC;

//     for(int i=0; i<=NUM_OF_NONTERMINALS; i++){
//         for(int j=0; j<=NUM_OF_TERMINALS; j++){
//             sync_set[i][j] = (j == semicol) || (j == bc) || (j == sqbc) || f1[i][j] || f2[i][j];
//         }
//     }
// }


// /*
// int main(){
//     bool f1[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
//     bool f1Done[NO_NON_TERMINALS];
//     for (int j = 0; j < 5; j++){
//         findf1(G[j]);
//     }
//     for(int i = 0; i < NO_TERMINALS; i++){
//         printf("%d ", f1[0][i]);
//     }
// }
// */

// int main(){
//     populate_grammar();
//     generateGrammar();
//     computef1andf2();
//     return 0;
// }


void findf1(lhs target){
    // printf("entering f1 %d\n", target.lhs_id);

    rhs *temp = target.firstRHS;
    // printf("TEMP asfaf: %d  Type: %d\n",temp ->rhs_id, temp ->isTerminal);
    rhs* temp2;
    //printf("TEMP RHS ID :%d \n",temp->rhs_id);
    if (temp->isTerminal == 1){
        //printf("LHS ID: %d ,RHS ID : %d",target.lhs_id, temp->rhs_id);
        // if(temp->rhs_id == NUM_OF_TERMINALS - 1){          
        //     temp2 = temp->nextRHS;
        //     if(temp2 != NULL){           
        //     int i = 0;
        //     for(i; i < NUM_OF_RULES; i++){
        //         if(temp2 == NULL){
        //             printf("FAIL");
        //         }
        //         if(G[i].lhs_id == temp2->rhs_id){
        //             break;
        //         }
        //     }
            
        //     findf1(G[i]);
        //     for(int i = 0; i < NUM_OF_TERMINALS; i++){
        //         if (f1[temp->rhs_id][i] == 1)
        //         f1[target.lhs_id][i] = f1[temp->rhs_id][i];
        //         f1Done[target.lhs_id] = 1;
        //     }
        //     }
        // }
        f1[target.lhs_id][temp->rhs_id] = 1;
        if(target.lhs_id == 2){
            printf("\n \n is terminal, fucked here\n \n");
        }
        // printf("Index: %d\n",temp -> rhs_id);
        f1Done[target.lhs_id] = 1;
    }
    else{
        // printf("inside repeated f1 and lhs is %d \n", target.lhs_id);

        if(target.lhs_id == 2){
            printf("\n \n fucked here\n \n");
        }
        if (f1Done[temp->rhs_id] == 0){
            
            for(int i = 0; i < NUM_OF_RULES; i++){
                if(G[i].lhs_id == temp->rhs_id){
                    findf1(G[i]);
                    // break;
                }
            }
            
        }
        for(int i = 0; i < NUM_OF_TERMINALS - 1; i++){
            if(f1[temp->rhs_id][i] == 1){
                printf("%d ", target.lhs_id);
                f1[target.lhs_id][i] = 1;
                if(target.lhs_id == 2){
                    printf("\n \ncorrect + some bt fucked here \n \n");
                }
            }
        }
        // if(target.f1RHS->nextRHS == NULL){
        //     printf("NULL HAI BHAI");
        //     // printf("temp ->rhs id :%d\n",target.f1RHS->nextRHS -> rhs_id);
        // }
        temp = temp->nextRHS;
        while (temp != NULL && f1[temp->rhs_id][NUM_OF_TERMINALS-1] == 1){
            // printf("Inside while loop\n");
            // printf("temp ->rhs id :%d\n",target.f1RHS-> rhs_id);
             
            // printf("TEMP IS TERMINAL: %d ",temp ->isTerminal);
            // printf("temp ->rhs id :%d\n",target.f1RHS->nextRHS -> rhs_id);
            if(temp != NULL){
                // printf("next rhs %d \n", temp->rhs_id);
                if (f1Done[temp->rhs_id] == 0){
                    // printf("Inside while loop f1 done\n");
                    for(int i = 0; i < NUM_OF_RULES; i++){
                        if(G[i].lhs_id == temp->rhs_id){
                            findf1(G[i]);
                            // break;
                        }
                    }
            
                }
            
            for(int i = 0; i < NUM_OF_TERMINALS - 1; i++){
                if(f1[temp->rhs_id][i] == 1){
                    f1[target.lhs_id][i] = 1;
                    if(target.lhs_id == 2){
                        printf("\n \nmultiple nts fucked here\n \n");
                    }
                }
            }
            temp = temp->nextRHS;
            }
            else{
                f1[target.lhs_id][NUM_OF_TERMINALS-1] = 1;
                break;
            }
        }
    }
    f1Done[target.lhs_id] = 1;
    // printf("f1 of arr_n4: %d",Fi)
}

void findf2(lhs start, rhs *target, rhs *temp){
    if (target->isTerminal == 1){
        return;
    }
    if(temp == NULL){
        // printf("Target RHS ID :%d \n",target ->rhs_id);
        for(int i =0; i < NUM_OF_TERMINALS; i++){
            f2[target->rhs_id][i] = f2[start.lhs_id][i];
        }
        return; 
    }
    if (temp->isTerminal == 1){
        f2[target->rhs_id][temp->rhs_id] = 1;
        return;
    }
    for(int i =0; i < NUM_OF_TERMINALS - 1; i++){
        if (f1[temp->rhs_id][i] == 1){
            f2[target->rhs_id][i] = 1;
        }
    }
    if(f1[temp->rhs_id][NUM_OF_TERMINALS - 1] == 0){
        return;
    }
    rhs *temp2 = temp->nextRHS;
    if(temp2 == NULL){
        for(int i =0; i < NUM_OF_TERMINALS; i++){
            if (f2[start.lhs_id][i] == 1)
            f2[target->rhs_id][i] = f2[start.lhs_id][i];
        }
        return; 
    }
    findf2(start, target, temp2);

}


void computef1andf2(){
    //lhs G1[NUM_OF_RULES];
    //G1= generateGrammar();
    for(int i=0;i<NUM_OF_NONTERMINALS;i++){
        f1Done[i]=0;
    }
    for(int j = NUM_OF_RULES - 1; j >= 0; j--){
        //printf("printing rule no %d ", j);
        printf("%d \n", j);
        findf1(G[j]);
    }

    for (int j = 0; j < NUM_OF_NONTERMINALS; j++){
        
            printf("\n%d\n%d\n", j, f1Done[j]);
        

        for(int i = 0; i < NUM_OF_TERMINALS; i++){
            printf("%d", f1[j][i]);
        }
    }

    f2[program][NUM_OF_TERMINALS - 1] = 1;

    for(int j = 0; j < NUM_OF_RULES; j++){
        rhs * target = G[j].firstRHS;
        while (target != NULL)
        {
            rhs * temp = target->nextRHS;
            findf2(G[j], target, temp); 
            target = temp;
        }       
    }

}

void loadFirstFollow() {
    FILE *g = fopen("firstArr.txt", "r");
    
    // read each line of the file and store its contents in the array
    for (int i = 0; i < NUM_OF_NONTERMINALS; i++) {
        char line[256];
        fgets(line, sizeof(line), g);
        
        // split the line into an array of integers
        char *token;
        int j = 0;
        token = strtok(line, ",");
        while (token != NULL) {
            First[i][j] = atoi(token);
            j++;
            token = strtok(NULL, ",");
        }
    }
    
    fclose(g);

    FILE *h = fopen("followArr.txt", "r");
    
    // read each line of the file and store its contents in the array
    for (int i = 0; i < NUM_OF_NONTERMINALS; i++) {
        char line[256];
        fgets(line, sizeof(line), h);
        
        // split the line into an array of integers
        char *token;
        int j = 0;
        token = strtok(line, ",");
        while (token != NULL) {
            Follow[i][j] = atoi(token);
            j++;
            token = strtok(NULL, ",");
        }
    }

    fclose(h);
}

int main(){
    generateGrammar();
    populate_grammar();
    computef1andf2();
    loadFirstFollow();


    for(int i = 0; i < NUM_OF_NONTERMINALS; i++){
        for(int j = 0; j < NUM_OF_TERMINALS; j++){
            if(First[i][j] != f1[i][j]){
                printf("Fucked first %d", i);
                break;
            }
            if(Follow[i][j] != f2[i][j]){
                printf("Fucked first %d", i);
                break;
            }
        }
        
    }

}
