#include "ll1_gram.h"
//#include "parser.h"
#include "lexer.h"

int Fir[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
int Ruledone[NUM_OF_RULES];
int Fol[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];


void find_first(){
    populate_grammar();
    generateGrammar();

    for(int i=0; i<NUM_OF_RULES; i++){
        // printf("%d\n", i);
        if(G[i].firstRHS->isTerminal){
            Fir[G[i].lhs_id][G[i].firstRHS->rhs_id] = 1;
            Ruledone[i] = 1; 
        }
    }

    int ch, ch1; 
    rhs* n;
    while(true){
        ch = 0;
        for(int i=0; i<NUM_OF_RULES; i++){
            if(Ruledone[i] == 0){
                ch1 = 0; 
                n = G[i].firstRHS;

                while(Fir[n->rhs_id][NUM_OF_TERMINALS-1] == 1 || n->nextRHS != NULL)
                for(int j=0; j<NUM_OF_TERMINALS; j++){
                    if(Fir[n->rhs_id][j] == 1 && Fir[G[i].lhs_id][j] == 0){
                        ch1 = 1;
                        Fir[G[i].lhs_id][j] = 1; 
                    }

                if(Fir[G[i].firstRHS->rhs_id][NUM_OF_TERMINALS-1] == 1){
                    n = G[i].firstRHS->nextRHS;
                    for(int j=0; j<NUM_OF_TERMINALS; j++){
                    if(Fir[n->rhs_id][j] == 1 && Fir[G[i].lhs_id][j] == 0){
                        ch1 = 1;
                        Fir[G[i].lhs_id][j] = 1; 
                    }
                }

                        
                }
                
            }
        // printf("%d\n", i);
    }     
    }




    for(int i=0; i<NUM_OF_RULES; i++){
        printf("%d", Ruledone[i]);
    }
    printf("\n");

}


int main(){
    find_first();
}