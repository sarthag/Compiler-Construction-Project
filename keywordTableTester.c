#include "keywordTable.h"

int main(){
    printf("Starting:\n");
    printf("Initializing keywordTable\n");
    
    initializeKeywordTable(keywordTable,KTSIZE);
    printf("keywordTable initialized\n");
    printf("HASH:%d\n",hash("integer"));
    insert("integer",INTEGER,keywordTable);
    insert("real",REAL,keywordTable);
    insert("boolean",BOOLEAN,keywordTable);
    insert("of",OF,keywordTable);
    insert("array",ARRAY,keywordTable);
    insert("start",START,keywordTable);
    insert("end",END,keywordTable);
    insert("declare",DECLARE,keywordTable);
    insert("module",MODULE,keywordTable);
    insert("driver",DRIVER,keywordTable);
    insert("program",PROGRAM,keywordTable);
    insert("get_value",GET_VALUE,keywordTable);
    insert("print",PRINT,keywordTable);
    insert("use",USE,keywordTable);
    insert("with",WITH,keywordTable);
    insert("parameters",PARAMETERS,keywordTable);
    insert("takes",TAKES,keywordTable);
    insert("input",INPUT,keywordTable);
    insert("returns",RETURNS,keywordTable);
    insert("for",FOR,keywordTable);
    insert("in",IN,keywordTable);
    insert("switch",SWITCH,keywordTable);
    insert("case",CASE,keywordTable);
    insert("break",BREAK,keywordTable);
    insert("default",DEFAULT,keywordTable);
    insert("while",WHILE,keywordTable);
    
    // printf("Inserted\n");
    printf("Printing keyword table\n");
    printKeywordTable(keywordTable,KTSIZE);
    printf("Done");
    printf("------TESTING GET---------\n");
    printf("LEXEME: %s , TOKEN: %d\n","integer",getTokenFromKT("integer",keywordTable));
    printf("LEXEME: %s , TOKEN: %d\n","for",getTokenFromKT("for",keywordTable));
    printf("LEXEME: %s , TOKEN: %d\n","while",getTokenFromKT("while",keywordTable));
    printf("LEXEME: %s , TOKEN: %d\n","switch",getTokenFromKT("switch",keywordTable));
    
}