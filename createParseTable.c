#include <stdio.h>
#include <stdlib.h>
#include "parserDef.h"
#include "parser.h"
#include <string.h>

//populate fake values of first and follow
bool first[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS+1] = {{1,1,0,1}, {1,1,0,1}, {0,1,0,1}, {0,0,1,0}};
bool follow[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS+1] = {{0,0,0,1}, {0,1,1,0}, {0,0,1,0}, {0,0,0,1}};

void populate_parse_table(){
    //populate the table with -1 
    for(int i=0;i<NUM_OF_NONTERMINALS;i++){
        for(int j=0;j<PT_COLS;j++){
            parse_table[i][j]=-1;
        }
    }
    for(int i=0;i<NUM_OF_RULES;i++){
        bool *first_set= first[G[i].lhs_id];
        for(int j=0; j<NUM_OF_TERMINALS;j++){
            if(first_set[j]==1){
                parse_table[G[i].lhs_id][j]=i;
            }
        } 
        if(first_set[NUM_OF_TERMINALS]==1){
            //if the first set contains epsilon
            bool* follow_set= follow[G[i].lhs_id];
            for(int k=0;k<NUM_OF_TERMINALS+1;k++){
                if(follow_set[k]==1){
                    parse_table[G[i].lhs_id][k]=i;
                }
            }
        }
    }
}

int main(){
    generateGrammar();
    populate_parse_table();
    for(int i=0;i<NUM_OF_NONTERMINALS;i++){
        for(int j=0;j<PT_COLS;j++){
            printf("%d ", parse_table[i][j]);
        }
        printf("\n");
    }
    return 0;
}
