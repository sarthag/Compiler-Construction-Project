/* Steps for building a lexer:
1.Create a twin buffer.
2. Read the input file and store it in the twin buffer.
3. Using the begin pointer and forward pointer and the switch case DFA find the lexeme.
4. Create a keyword hashtable
5. When you reach the fin state do the needful.
6. If identifier then check hashtable for keyword.
7. Create a linked list for tokens. Store the tokens in a form of a linked list*/

#include "lexer.h"

FILE* readFile(){
    FILE *code = fopen("testCode.txt", "r");
    return code; 
}

FILE* getStream(FILE *code){
    
}