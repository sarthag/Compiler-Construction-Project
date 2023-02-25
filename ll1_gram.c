#include <stdio.h>
#include <stdlib.h>
#include "parserDef.h"
#include "parser.h"
#include <string.h>

#define MAX_LINE_LENGTH 50
#define NO_NON_TERMINALS 4
#define NO_TERMINALS 3
char *non_terminals[]={"start", "module", "otherModules", "moduleDef"};
char *terminals[]={"NUM", "ID", "COLON"};

int get_id(char *str, int t){
    //printf("call to get id ");
    //t= 0 for non terminal and 1 and terminal
    if(t==0){
        for(int i=0;i< NO_NON_TERMINALS; i++ ){
            if(strcmp(non_terminals[i], str)==0){
                printf("strcmp value %d ", strcmp(non_terminals[i], str));
                printf("%s \n", non_terminals[i]);
                return i;
            }
        printf("%s non_terminal : Symbol doesn't exist %s \n", str, non_terminals[i]);
        }
    }
    else {
        for(int i=0;i< NO_TERMINALS; i++ ){
        if(strcmp(terminals[i], str)==0){
            return i;
        }
        printf("%s terminal : Symbol doesn't exist %s \n", str, terminals[i]);
    }
    }

    return -1;
    
}
bool isTerm(char* str){
    if(str[0] >= 65 && str[0]<= 90){
        return 1;
    }
    else if(str[0]>=97 && str[0]<=122){
        return 0;
    }
    return -1;
}

/*
void addLinkedList(char* lineBuf, int count){
    printf("entering add ll  \n ");
    char str[20];
    int wc=0;
    for(int i=0; i<strlen(lineBuf); i++){
        if(lineBuf[i]=='\n'){
            //do something
            return ;
        }
        else if(lineBuf[i]==' '){
            //do something
            char *str1 = (char*)malloc(sizeof(char)*wc);
            strcpy(str1, str);
            printf("%s ", str1);
            wc=0;
            memset(str, '\0', sizeof(str));
        }
        else{
            str[wc] = lineBuf[i];
            wc=wc+1;
        }
    }
    printf("\n");
}
*/


/*
void generateGrammar(){
    FILE *fp = fopen("grammar_fake.txt", "r");
    if(fp ==NULL){
        printf("Error in opening the file ");
    }
    char ch;
    int count = 0;
    char *lineBuf = (char *)malloc(sizeof(char)*MAX_LINE_LENGTH);
    //char *lineBuf1 = (char *)malloc(sizeof(char)*MAX_LINE_LENGTH);
    memset(lineBuf, ' ', MAX_LINE_LENGTH);
    while(ch != EOF){
        ch=getc(fp);
        if(ch!='\n'){
            lineBuf[count]=ch;
            count=count + 1;
        }
        else{
            //when we reach the end of line 
            addLinkedList(lineBuf, count);
            count = 0;
            memset(lineBuf, ' ', MAX_LINE_LENGTH);
        }
    }
    addLinkedList(lineBuf, count);

}

*/

void generateGrammar(){
    FILE *fp = fopen("grammar_fake.txt", "r");
    if(fp ==NULL){
        printf("Error in opening the file ");
    }
    char lineBuf[MAX_LINE_LENGTH];
    int rule_no = 0;
    rhs temp_rhs;
    rhs prev_rhs;
    while(fgets(lineBuf, sizeof(lineBuf), fp)!=NULL ){
        char *str;
        str=strtok(lineBuf, " \n");
        for(int i=0;str!=NULL; i++){
            if(i==0){
                //printf("%s\n", str);
                //this is the lhs
                G[rule_no].lhs_id=  get_id(str, 0);
                G[rule_no].firstRHS=NULL;
            }
            else {
                //printf("%s\n", str);
                //this is the rhs 
                if(G[rule_no].firstRHS==NULL){
                    temp_rhs.isTerminal=isTerm(str);
                    printf("value of t is %d \n", temp_rhs.isTerminal);
                    temp_rhs.rhs_id= get_id(str, temp_rhs.isTerminal);
                    temp_rhs.nextRHS= NULL;
                    G[rule_no].firstRHS=&(temp_rhs);
                    prev_rhs=temp_rhs;
                }
                else{
                    //not the first rhs rule
                    temp_rhs.isTerminal=isTerm(str);
                    temp_rhs.rhs_id= get_id(str, temp_rhs.isTerminal);
                    temp_rhs.nextRHS= NULL;
                    prev_rhs.nextRHS= &temp_rhs;
                    prev_rhs=temp_rhs;
                }
            }
            str=strtok(NULL, " \n");
        }

        printf("\n");
    }

}
int main(){
    generateGrammar();
    return 0;
}

