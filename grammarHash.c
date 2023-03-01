#include "grammarHash.h"

//common stuff
int hashGrammar(const char *element){
    long long prime = PRIME;
    long long hashVal = 0;
    long long primePower = 1;
    long long mod = MOD;
    int size = strlen(element);
    for(int i = 0  ; i < size ; i++){
        hashVal = (hashVal + ((element[i]-'A'+1)*primePower)) % mod;
        primePower = (primePower + 1) % mod;
    }

    return hashVal;
}

//for non terminals
void initializeNTTable(ntElement ntTable[], int size){
    for(int i = 0; i < size; i++){
        ntTable[i].occupied = false;
    }
}

//open addressing for collisions
void insertNonTerminal(const char *ntText, nt_key nonTerminal, ntElement ntTable[]){
    int i = 0;
    int hashValue = hashGrammar(ntText);
    int index = hashValue % NTSIZE;
    printf("Inserted %s initially at INDEX : %d\n", ntText ,index);
    while (ntTable[index].occupied ==true){
        i++;
        index  = (hashValue + (i*i))%NTSIZE;
    }
    int ntTextSize = NTTEXTSIZE;
    // strncpy(keywordTable[index].lexeme, lexeme, lexemeSize-1);
    // keywordTable[index].lexeme[lexemeSize -1] = '\0';
    strcpy(ntTable[index].ntText, ntText);
    ntTable[index].nonTerminal = nonTerminal;
    
    ntTable[index].occupied = true;
    printf("Inserted %s at INDEX : %d\n", ntText ,index);
}


nt_key getTokenFromNTTable(char *ntText, ntElement ntTable[]){
    int i = 0;
    int hashValue = hashGrammar(ntText);
    int index = hashValue % NTSIZE;
    while (ntTable[index].occupied){
        if(strcmp(ntText, ntTable[index].ntText) == 0){
            return ntTable[index].nonTerminal;
        }
        i++;
        index  = (hashValue + (i*i))%NTSIZE;
    }
    return -1;
}


void printNTTable(ntElement ntTable[], int ntSize){
    for(int i = 0 ; i < ntSize ; i++){
        printf("%d: ",i);
        printf("Lexeme : %s\n", ntTable[i].ntText);
        printf("token: %d\n", ntTable[i].nonTerminal);
        printf("occupied : %s\n",ntTable[i].occupied?"true":"false");
    }
}

//for terminals
void initializeTTable(tElement tTable[], int size){
    for(int i = 0; i < size; i++){
        tTable[i].occupied = false;
    }
}

void insertTerminal(const char *tText, token_key terminal, tElement tTable[]){
    int i = 0;
    int hashValue = hashGrammar(tText);
    int index = hashValue % TSIZE;
    printf("Inserted %s initially at INDEX : %d\n", tText ,index);
    while (tTable[index].occupied ==true){
        i++;
        index  = (hashValue + (i*i))%TSIZE;
    }
    int ntTextSize = NTTEXTSIZE;
    // strncpy(keywordTable[index].lexeme, lexeme, lexemeSize-1);
    // keywordTable[index].lexeme[lexemeSize -1] = '\0';
    strcpy(tTable[index].tText, tText);
    tTable[index].terminal = terminal;
    
    tTable[index].occupied = true;
    printf("Inserted %s at INDEX : %d\n", tText ,index);
}


token_key getTokenFromTTable(char *tText, tElement tTable[]){
    int i = 0;
    int hashValue = hashGrammar(tText);
    int index = hashValue % TSIZE;
    while (tTable[index].occupied){
        if(strcmp(tText, tTable[index].tText) == 0){
            return tTable[index].terminal;
        }
        i++;
        index  = (hashValue + (i*i))%TSIZE;
    }
    return -1;
}


void printTTable(tElement tTable[], int tSize){
    for(int i = 0 ; i < tSize ; i++){
        printf("%d: ",i);
        printf("Lexeme : %s\n", tTable[i].tText);
        printf("token: %d\n", tTable[i].terminal);
        printf("occupied : %s\n",tTable[i].occupied?"true":"false");
    }
}