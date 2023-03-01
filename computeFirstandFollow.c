// #include "computeFirstandFollow.h"

// void findFirst(lhs target){
//     printf("here %d\n", target.lhs_id);
//     rhs *temp = target.firstRHS;
//     if (temp->isTerminal == 1){
//         if(temp->rhs_id == NUM_OF_TERMINALS - 1){      
//             rhs* temp2 = temp->nextRHS;
//             if(temp2 != NULL){           
//             int i = 0;
//             for(i; i < NUM_OF_RULES; i++){
//                 if(G[i].lhs_id == temp2->rhs_id){
//                     break;
//                 }
//             }
            
//             findFirst(G[i]);
//             for(int i = 0; i < NUM_OF_TERMINALS; i++){
//                 if (First[temp->rhs_id][i] == 1)
//                 First[target.lhs_id][i] = First[temp->rhs_id][i];
//                 firstDone[target.lhs_id] = 1;
//             }
//             }
//         }
//         First[target.lhs_id][temp->rhs_id] = 1;
//         firstDone[target.lhs_id] = 1;
//     }
//     else{
//         if (firstDone[temp->rhs_id] == 0){
//             int i = 0;
//             for(i; i < NUM_OF_RULES; i++){
//                 if(G[i].lhs_id == temp->rhs_id){
//                     break;
//                 }
//             }
            
//             findFirst(G[i]);
//         }
//         for(int i = 0; i < NUM_OF_TERMINALS; i++){
//             if(First[temp->rhs_id][i] == 1)
//             First[target.lhs_id][i] = First[temp->rhs_id][i];
//             firstDone[target.lhs_id] = 1;
//         }
//     }
// }

// void findFollow(lhs start, rhs *target, rhs *temp){
//     if (target->isTerminal == 1){
//         return;
//     }
//     if(temp == NULL){
//         for(int i =0; i < NUM_OF_TERMINALS; i++){
//             Follow[target->rhs_id][i] = Follow[start.lhs_id][i];
//         }
//         return; 
//     }
//     if (temp->isTerminal == 1){
//         Follow[target->rhs_id][temp->rhs_id] = 1;
//         return;
//     }
//     for(int i =0; i < NUM_OF_TERMINALS - 1; i++){
//         if (First[temp->rhs_id][i] == 1){
//             Follow[target->rhs_id][i] = First[temp->rhs_id][i];
//         }
//     }
//     if(First[temp->rhs_id][NUM_OF_TERMINALS - 1] == 0){
//         return;
//     }
//     rhs *temp2 = temp->nextRHS;
//     if(temp2 == NULL){
//         for(int i =0; i < NUM_OF_TERMINALS; i++){
//             if (Follow[start.lhs_id][i] == 1)
//             Follow[target->rhs_id][i] = Follow[start.lhs_id][i];
//         }
//         return; 
//     }
//     findFollow(start, target, temp2);

// }


// void computeFirstandFollow(){
//     //lhs G1[NUM_OF_RULES];
//     //G1= generateGrammar();
//     for(int j = NUM_OF_RULES - 1; j >= 0; j--){
//         findFirst(G[j]);
//     }

//     for (int j = 0; j < NUM_OF_NONTERMINALS; j++){
//         printf("\n%d\n%d\n", j, firstDone[j]);

//         for(int i = 0; i < NUM_OF_TERMINALS; i++){
//             printf("%d", First[j][i]);
//         }
//     }

//     Follow[0][NUM_OF_TERMINALS - 1] = 1;

//     for(int j = 0; j < NUM_OF_RULES; j++){
//         rhs * target = G[j].firstRHS;
//         while (target != NULL)
//         {
//             rhs * temp = target->nextRHS;
//             findFollow(G[j], target, temp); 
//             target = temp;
//         }       
//     }

//     for (int j = 0; j < NUM_OF_NONTERMINALS; j++){
//         printf("\n");
//         for(int i = 0; i < NUM_OF_TERMINALS; i++){
            
//             printf("%d", Follow[j][i]);
//         }      
//     }
// }

// void syncronization_set(){
//     token_key semicol = SEMICOL, bc = BC, sqbc = SQBC;

//     for(int i=0; i<=NUM_OF_NONTERMINALS; i++){
//         for(int j=0; j<=NUM_OF_TERMINALS; j++){
//             sync_set[i][j] = (j == semicol) || (j == bc) || (j == sqbc) || First[i][j] || Follow[i][j];
//         }
//     }
// }


// /*
// int main(){
//     bool First[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
//     bool firstDone[NO_NON_TERMINALS];
//     for (int j = 0; j < 5; j++){
//         findFirst(G[j]);
//     }
//     for(int i = 0; i < NO_TERMINALS; i++){
//         printf("%d ", First[0][i]);
//     }
// }
// */

// int main(){
//     populate_grammar();
//     generateGrammar();
//     computeFirstandFollow();
//     return 0;
// }