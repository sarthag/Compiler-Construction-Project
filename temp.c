#include "astadt.h"

#define NUM_OF_RELAVENT 2

char* relavent[NUM_OF_RELAVENT] = {"PLUS", "MINUS"};
int lables[NUM_OF_TERMINALS] = {0};


void populateLabels(){
    token_key tk;
    for(int i=0; i<NUM_OF_RELAVENT; i++){
        tk = getTokenFromTTable(relavent[i], terminalHash);
        lables[tk] = 1; 
    }
}