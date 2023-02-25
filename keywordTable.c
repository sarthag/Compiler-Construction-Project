#include "keywordTable.h"

//implementing a polynomial rolling hash
int hash(char *lexeme){
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

void initializeKeyWordTable(ktElement keywordTable[], int size){
    for(int i = 0; i < size; i++){
        keywordTable[i].occupied = false;
    }
}

//open addressing for collisions
void insert(char *lexeme, int token, ktElement keywordTable[]){
    int i = 0;
    int hashValue = hash(lexeme);
    int index = hashValue % KTSIZE;
    while (keywordTable[index].occupied){
        if(strcmp(lexeme, keywordTable[index].lexeme) == 0){
            break;
        }
        i++;
        index  = (hashValue + (i*i))%KTSIZE;
    }
    strcpy(keywordTable[index].lexeme,lexeme);
    keywordTable[index].token = token;
    keywordTable[index].occupied = true;
}

int get(char *lexeme, ktElement keywordTable[]){
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