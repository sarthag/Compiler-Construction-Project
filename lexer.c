/* Steps for building a lexer:
1. Create a twin buffer.
2. Read the input file and store it in the twin buffer.
3. Using the begin pointer and forward pointer and the switch case DFA find the lexeme.
4. Create a keyword hashtable
5. When you reach the fin state do the needful.
6. If identifier then check hashtable for keyword.
7. Create a linked list for tokens. Store the tokens in a form of a linked list*/

#include "lexer.h"

twinBuffer buffers;
line_no = 1; 
numChar = 0;

FILE* readFile(char *filename){
    FILE *code = fopen(filename , "r");
    return code; 
}

FILE* getStream(FILE *code){
    if(code == NULL) {
        printf('File Opening Error!\n');
        return NULL;
    }

    if (!started) {
        memset(buffers.buffer1, 0, BUFFERSIZE+1);
        memset(buffers.buffer1, 0, BUFFERSIZE+1);

        eof = false;
        read1 = false;
        read2 = false;
        started = false;

        lexeme = NULL;
        forward = NULL;

        int buf_size1 = fread(buffers.buffer1, sizeof(char), BUFFERSIZE, code);
        buffers.buffer1[buf_size1] = '\0';
        lexeme = buffers.buffer1;    
        forward = buffers.buffer1;
        started = true;
        read1 = true;
        read2 = false;
    }

    else if (forward == buffers.buffer1 + BUFFERSIZE - 1) {
        if (!read2) {
            int buf_size2 = fread(buffers.buffer2, sizeof(char), BUFFERSIZE, code);
            buffers.buffer2[buf_size2] = '\0';
        }
        forward = buffers.buffer2;
        read2 = true;
        read1 = false;
    }

    else if (forward == buffers.buffer2 + BUFFERSIZE - 1) {
        if (!read1) {
            int buf_size2 = fread(buffers.buffer1, sizeof(char), BUFFERSIZE, code);
            buffers.buffer1[buf_size2] = '\0';
        }
        forward = buffers.buffer1;
        read1 = true;
        read2 = false;
    }

    else {
        forward++;
    }

    return code;
}

char getNextChar(FILE* code) {
    char current = *forward;
    if (!started) {
        numChar++;
        forward++;
    }
    else {
        code = getStream(code);
        numChar++;
    }
    return current;
}

void retract(int num_char){

}

// int insert(char *lexeme, int token, ktElement keywordTable[]);
void populate_keyword_table(){
    insert("AND", AND, keyword_table);
    insert("array", ARRAY, keyword_table);
    insert("boolean", BOOLEAN, keyword_table);
    insert("break", BREAK, keyword_table);
    insert("case", CASE, keyword_table);
    insert("declare", DECLARE, keyword_table);
    insert("default", DEFAULT, keyword_table);
    insert("end", END, keyword_table);
    insert("for", FOR, keyword_table);
    insert("get_value", GET_VALUE, keyword_table);
    insert("in", IN, keyword_table);
    insert("input", INPUT, keyword_table);
    insert("integer", INTEGER, keyword_table);
    insert("module", MODULE, keyword_table);
    insert("of", OF, keyword_table);
    insert("OR", OR, keyword_table);
    insert("parameters", PARAMETERS, keyword_table);
    insert("print", PRINT, keyword_table);
    insert("program", PROGRAM, keyword_table);
    insert("real", REAL, keyword_table);
    insert("returns", RETURNS, keyword_table);
    insert("start", START, keyword_table);
    insert("switch", SWITCH, keyword_table);
    insert("takes", TAKES, keyword_table);
    insert("use", USE, keyword_table);
    insert("while", WHILE, keyword_table);
    insert("with", WITH, keyword_table);
    insert("false", FALSE, keyword_table);
    insert("true", TRUE, keyword_table);
}


// char* get(char *lexeme, ktElement keywordTable[]);
token_key search_keyword_table(char* lexeme){
    int key = get(lexeme, keyword_table);
    if(key == -1){
        return ID; 
    }
    else{
        return key;
    }
}


void init_lexer(){
    
}