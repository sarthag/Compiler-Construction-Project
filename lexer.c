/* Steps for building a lexer:
1.Create a twin buffer.
2. Read the input file and store it in the twin buffer.
3. Using the begin pointer and forward pointer and the switch case DFA find the lexeme.
4. Create a keyword hashtable
5. When you reach the fin state do the needful.
6. If identifier then check hashtable for keyword.
7. Create a linked list for tokens. Store the tokens in a form of a linked list*/

#include "lexer.h"

FILE* readFile(char *filename){
    FILE *code = fopen(filename , "r");
    return code; 
}

FILE* getStream(FILE *code){

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
    insert("parameters", PARMETERS, keyword_table);
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
