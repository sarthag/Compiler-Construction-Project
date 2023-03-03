// ------------------------------------------------
// GROUP 06 

// ANSHIKA GUPTA 2020A7PS0111P
// NIVEDITHA KOVILAKATH 2020A7PS0067P
// SHAZ 2020A7PS0025P
// SARTHAK AGARWAL 2020A7PS0112P
// SHREYAS SESHAM 2020A7PS1684P
// ------------------------------------------------


#include "keywordTable.h"

//implementing a polynomial rolling hash
int hash(const char *lexeme){
    long long prime = PRIME;
    long long hashVal = 0;
    long long primePower = 1;
    long long mod = MOD;
    int size = strlen(lexeme);
    for(int i = 0  ; i < size ; i++){
        hashVal = (hashVal + ((lexeme[i]-'a'+1)*primePower)) % mod;
        primePower = (primePower + 1) % mod;
    }

    return hashVal;
}

void initializeKeywordTable(ktElement keywordTable[], int size){
    for(int i = 0; i < size; i++){
        keywordTable[i].occupied = false;
    }
}

//open addressing for collisions
void insert(const char *lexeme, token_key token, ktElement keywordTable[]){
    int i = 0;
    int hashValue = hash(lexeme);
    int index = hashValue % KTSIZE;
    // printf("Inserted %s initially at INDEX : %d\n", lexeme ,index);
    while (keywordTable[index].occupied ==true){
        i++;
        index  = (hashValue + (i*i))%KTSIZE;
    }
    int lexemeSize = LEXEMESIZE;
    // strncpy(keywordTable[index].lexeme, lexeme, lexemeSize-1);
    // keywordTable[index].lexeme[lexemeSize -1] = '\0';
    strcpy(keywordTable[index].lexeme, lexeme);
    keywordTable[index].token = token;
    
    keywordTable[index].occupied = true;
    // printf("Inserted %s at INDEX : %d\n", lexeme ,index);
}


token_key getTokenFromKT(char *lexeme, ktElement keywordTable[]){
    int i = 0;
    int hashValue = hash(lexeme);
    int index = hashValue % KTSIZE;
    while (keywordTable[index].occupied){
        if(strcmp(lexeme, keywordTable[index].lexeme) == 0){
            return keywordTable[index].token;
        }
        i++;
        index  = (hashValue + (i*i))%KTSIZE;
    }
    return -1;
}


void printKeywordTable(ktElement keywordTable[], int ktSize){
    for(int i = 0 ; i < ktSize ; i++){
        printf("%d: ",i);
        printf("Lexeme : %s\n", keywordTable[i].lexeme);
        printf("token: %d\n", keywordTable[i].token);
        printf("occupied : %s\n",keywordTable[i].occupied?"true":"false");
    }
}

