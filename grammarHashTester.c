#include "grammarHash.h"

int main(){
    printf("Starting:\n");
    printf("Initializing NTTable\n");
    
    initializeNTTable(nonTerminalHash,NTSIZE);
    printf("Non Terminal HashTable initialized\n");
    // insertNonTerminal("STARTCODE",STARTCODE,nonTerminalHash);
    printNTTable(nonTerminalHash,NTSIZE);
    printf("Done");
    printf("------TESTING GET---------\n");
    printf("NT TEXT: %s , NON TERMINAL: %d\n","STARTCODE",getTokenFromNTTable("STARTCODE",nonTerminalHash));
    printf("LEXEME: %s , TOKEN: %d\n","for",getTokenFromNTTable("for",nonTerminalHash));
    
    initializeTTable(terminalHash,TSIZE);
    printf("terminalHash initialized\n");
    insertTerminal("integer",INTEGER,terminalHash);
    insertTerminal("real",REAL,terminalHash);
    insertTerminal("boolean",BOOLEAN,terminalHash);
    insertTerminal("of",OF,terminalHash);
    insertTerminal("array",ARRAY,terminalHash);
    insertTerminal("start",START,terminalHash);
    insertTerminal("end",END,terminalHash);
    insertTerminal("declare",DECLARE,terminalHash);
    insertTerminal("module",MODULE,terminalHash);
    insertTerminal("driver",DRIVER,terminalHash);
    insertTerminal("program",PROGRAM,terminalHash);
    insertTerminal("get_value",GET_VALUE,terminalHash);
    insertTerminal("print",PRINT,terminalHash);
    insertTerminal("use",USE,terminalHash);
    insertTerminal("with",WITH,terminalHash);
    insertTerminal("parameters",PARAMETERS,terminalHash);
    insertTerminal("takes",TAKES,terminalHash);
    insertTerminal("input",INPUT,terminalHash);
    insertTerminal("returns",RETURNS,terminalHash);
    insertTerminal("for",FOR,terminalHash);
    insertTerminal("in",IN,terminalHash);
    insertTerminal("switch",SWITCH,terminalHash);
    insertTerminal("case",CASE,terminalHash);
    insertTerminal("break",BREAK,terminalHash);
    insertTerminal("default",DEFAULT,terminalHash);
    insertTerminal("while",WHILE,terminalHash);
    
    // printf("insertTerminaled\n");
    printf("Printing keyword table\n");
    printTTable(terminalHash,TSIZE);
    printf("Done");
    printf("------TESTING GET---------\n");
    printf("LEXEME: %s , TOKEN: %d\n","integer",getTokenFromTTable("integer",terminalHash));
    printf("LEXEME: %s , TOKEN: %d\n","for",getTokenFromTTable("for",terminalHash));
    printf("LEXEME: %s , TOKEN: %d\n","while",getTokenFromTTable("while",terminalHash));
    printf("LEXEME: %s , TOKEN: %d\n","switch",getTokenFromTTable("switch",terminalHash));
    printf("LEXEME: %s , TOKEN: %d\n","nigga",getTokenFromTTable("nigga",terminalHash));
    
    // printf("Inserted\n");
    
    
}