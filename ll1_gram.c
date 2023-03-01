#include "ll1_gram.h"


//char *non_terminals[]={"start", "module", "otherModules", "moduleDef"};
//char *terminals[]={"NUM", "ID", "COLON", "EPSILON"};
/*
int get_id(char *str, int t){
    //printf("call to get id ");
    //t= 0 for non terminal and 1 and terminal
    //the id for epsilong is -1
    //id returned is -2 if it isn't detected 
    if(strcmp(str, "epsilon")==0){
        return -1;
    }
    if(t==0){
        for(int i=0;i< NUM_OF_NONTERMINALS; i++ ){
            if(strcmp(non_terminals[i], str)==0){
                //printf("strcmp value %d ", strcmp(non_terminals[i], str));
                //printf("%s \n", non_terminals[i]);
                return i;
            }
        //printf("%s non_terminal : Symbol doesn't exist %s \n", str, non_terminals[i]);
        }
    }
    else {
        for(int i=0;i< NUM_OF_TERMINALS; i++ ){
        if(strcmp(terminals[i], str)==0){
            return i;
        }
        //printf("%s terminal : Symbol doesn't exist %s \n", str, terminals[i]);
    }
    }
    printf("not detected \n");
    return -2;
    
}
*/ 
bool isTerm(char* str){
    if(str[0] >= 65 && str[0]<= 90){
        return 1;
    }
    else{
        return 0;
    }
    return -1;
}


void generateGrammar(){
    FILE *fp = fopen("grammar_fake.txt", "r");
    if(fp ==NULL){
        printf("Error in opening the file ");
    }
    char lineBuf[MAX_LINE_LENGTH];
    int rule_no = 0;
    
    while(fgets(lineBuf, sizeof(lineBuf), fp)!=NULL ){
        char *str;
        rhs *firstRHS = NULL;
        rhs *prev_rhs = NULL;

        str=strtok(lineBuf, " \n");
        for(int i = 0; str != NULL; i++){
            if(i==0){
                //lhs non_terminal
                G[rule_no].lhs_id = getTokenFromNTTable(str, nonTerminalHash);
                G[rule_no].firstRHS = NULL;   
            }
            else {
                rhs *new_rhs = (rhs *)malloc(sizeof(rhs));
                new_rhs->isTerminal = isTerm(str);
                new_rhs->rhs_id = getTokenFromTTable(str, terminalHash);
                new_rhs->nextRHS = NULL;
                
                if(prev_rhs==NULL){
                    //first rule of rhs 
                    firstRHS = new_rhs;
                }
                else{
                    //other rules of rhs
                    prev_rhs->nextRHS = new_rhs;
                }
                
                new_rhs->prevRHS = prev_rhs;
                prev_rhs = new_rhs;
                
            }
            str=strtok(NULL, " \n");
        }
        G[rule_no].firstRHS = firstRHS;
        G[rule_no].lastRHS = prev_rhs;
        rule_no++;
    }


}



void populate_grammar(){
    initializeTTable(terminalHash, TSIZE);
    initializeNTTable(nonTerminalHash, NTSIZE);
    insertTerminal("AND", AND, terminalHash);
    insertTerminal("ARRAY", ARRAY, terminalHash);
    insertTerminal("ASSIGNOP", ASSIGNOP, terminalHash);
    insertTerminal("BC", BC, terminalHash);
    insertTerminal("BO", BO, terminalHash);
    insertTerminal("BOOLEAN", BOOLEAN, terminalHash);
    insertTerminal("BREAK", BREAK, terminalHash);
    insertTerminal("CASE", CASE, terminalHash);
    insertTerminal("COLON", COLON, terminalHash);
    insertTerminal("COMMA", COMMA, terminalHash);
    insertTerminal("DECLARE", DECLARE, terminalHash);
    insertTerminal("DEF", DEF, terminalHash);
    insertTerminal("DEFAULT", DEFAULT, terminalHash);
    insertTerminal("DIV", DIV, terminalHash);
    insertTerminal("DRIVER", DRIVER, terminalHash);
    insertTerminal("DRIVERDEF", DRIVERDEF, terminalHash);
    insertTerminal("DRIVERENDDEF", DRIVERENDDEF, terminalHash);
    insertTerminal("END", END, terminalHash);
    insertTerminal("ENDDEF", ENDDEF, terminalHash);
    insertTerminal("EQ", EQ, terminalHash);
    insertTerminal("FALSE", FALSE, terminalHash);
    insertTerminal("FOR", FOR, terminalHash);
    insertTerminal("GE", GE, terminalHash);
    insertTerminal("GET_VALUE", GET_VALUE, terminalHash);
    insertTerminal("GT", GET_VALUE, terminalHash);
    insertTerminal("ID", GET_VALUE, terminalHash);
    insertTerminal("IN", GET_VALUE, terminalHash);
    insertTerminal("INPUT", GET_VALUE, terminalHash);
    insertTerminal("INTEGER", GET_VALUE, terminalHash);
    insertTerminal("LE", GET_VALUE, terminalHash);
    insertTerminal("LT", GET_VALUE, terminalHash);
    insertTerminal("MINUS", GET_VALUE, terminalHash);
    insertTerminal("MODULE", GET_VALUE, terminalHash);
    insertTerminal("MUL", GET_VALUE, terminalHash);
    insertTerminal("NE", GET_VALUE, terminalHash);
    insertTerminal("NUM", GET_VALUE, terminalHash);
    insertTerminal("OF", GET_VALUE, terminalHash);
    insertTerminal("OR", GET_VALUE, terminalHash);
    insertTerminal("PARAMETERS", GET_VALUE, terminalHash);
    insertTerminal("PLUS", GET_VALUE, terminalHash);
    insertTerminal("PRINT", GET_VALUE, terminalHash);
    insertTerminal("PROGRAM", GET_VALUE, terminalHash);
    insertTerminal("NUM", GET_VALUE, terminalHash);
    insertTerminal("NUM", GET_VALUE, terminalHash);
    insertTerminal("NUM", GET_VALUE, terminalHash);
    insertTerminal("NUM", GET_VALUE, terminalHash);
    insertTerminal("RANGEOP", RANGEOP, terminalHash);
    insertTerminal("REAL", REAL, terminalHash);
    insertTerminal("RETURNS", RETURNS, terminalHash);
    insertTerminal("RNUM", RNUM, terminalHash);
    insertTerminal("SEMICOL", SEMICOL, terminalHash);
    insertTerminal("SQBO", SQBO, terminalHash);
    insertTerminal("SQBC", SQBC, terminalHash);
    insertTerminal("START", START, terminalHash);
    insertTerminal("SWITCH", SWITCH, terminalHash);
    insertTerminal("TAKES", TAKES, terminalHash);
    insertTerminal("TRUE", TRUE, terminalHash);
    insertTerminal("USE", USE, terminalHash);
    insertTerminal("WHILE", WHILE, terminalHash);
    insertTerminal("WITH", WITH, terminalHash);
    insertTerminal("EPSILON", EPSILON, terminalHash);
    //POPULATING NON TERMINALS TABLE 
    
    insertNonTerminal("anyTerm", anyTerm, nonTerminalHash);
    insertNonTerminal("arithmeticExpr", arithmeticExpr, nonTerminalHash);
    insertNonTerminal("arithmeticOrBooleanExpr", arithmeticOrBooleanExpr, nonTerminalHash);
    insertNonTerminal("arrExpr", arrExpr, nonTerminalHash);
    insertNonTerminal("arrFactor", arrFactor, nonTerminalHash);
    insertNonTerminal("arrTerm", arrTerm, nonTerminalHash);
    insertNonTerminal("arr_N4", arr_N4, nonTerminalHash);
    insertNonTerminal("arr_N5", arr_N5, nonTerminalHash);
    insertNonTerminal("array_element_for_print", array_element_for_print, nonTerminalHash);
    insertNonTerminal("assignmentStmt", assignmentStmt, nonTerminalHash);
    insertNonTerminal("boolConstt", boolConstt, nonTerminalHash);
    insertNonTerminal("caseStmt1", caseStmt1, nonTerminalHash);
    insertNonTerminal("caseStmt2", caseStmt2, nonTerminalHash);
    insertNonTerminal("conditionalStmt", conditionalStmt, nonTerminalHash);
    insertNonTerminal("dataType", dataType, nonTerminalHash);
    insertNonTerminal("declareStmt", declareStmt, nonTerminalHash);
    insertNonTerminal("default1", default1, nonTerminalHash);
    insertNonTerminal("driverModule", driverModule, nonTerminalHash);
    insertNonTerminal("element_index_with_expressions", element_index_with_expressions, nonTerminalHash);
    insertNonTerminal("expression", expression, nonTerminalHash);
    insertNonTerminal("factor", factor, nonTerminalHash);
    insertNonTerminal("idList1", idList1, nonTerminalHash);
    insertNonTerminal("idList2", idList2, nonTerminalHash);
    insertNonTerminal("id_num_rnum", id_num_rnum, nonTerminalHash);
    insertNonTerminal("index_arr", index_arr, nonTerminalHash);
    insertNonTerminal("index_for_loop", index_for_loop, nonTerminalHash);
    insertNonTerminal("input_plist1", input_plist1, nonTerminalHash);
    insertNonTerminal("input_plist2", input_plist2, nonTerminalHash);
    insertNonTerminal("ioStmt", ioStmt, nonTerminalHash);
    insertNonTerminal("iterativeStmt", iterativeStmt, nonTerminalHash);
    insertNonTerminal("logicalOp", logicalOp, nonTerminalHash);
    insertNonTerminal("module", module, nonTerminalHash);
    insertNonTerminal("moduleDeclaration", moduleDeclaration, nonTerminalHash);
    insertNonTerminal("moduleDeclarations", moduleDeclarations, nonTerminalHash);
    insertNonTerminal("moduleDef", moduleDef, nonTerminalHash);
    insertNonTerminal("moduleReuseStmt", moduleReuseStmt, nonTerminalHash);
    insertNonTerminal("n1", n1, nonTerminalHash);
    insertNonTerminal("n2", n2, nonTerminalHash);
    insertNonTerminal("n3", n3, nonTerminalHash);
    insertNonTerminal("n4", n4, nonTerminalHash);
    insertNonTerminal("n5", n5, nonTerminalHash);
    insertNonTerminal("n6", n6, nonTerminalHash);
    insertNonTerminal("new_NT", new_NT, nonTerminalHash);
    insertNonTerminal("new_index", new_index, nonTerminalHash);
    insertNonTerminal("new_indexSQBC", new_indexSQBC, nonTerminalHash);
    insertNonTerminal("new_index_for_loop", new_index_for_loop, nonTerminalHash);
    insertNonTerminal("op1", op1, nonTerminalHash);
    insertNonTerminal("op2", op2, nonTerminalHash);
    insertNonTerminal("optional", optional, nonTerminalHash);
    insertNonTerminal("otherModules", otherModules, nonTerminalHash);
    insertNonTerminal("output_plist1", output_plist1, nonTerminalHash);
    insertNonTerminal("output_plist2", output_plist2, nonTerminalHash);
    insertNonTerminal("p1", p1, nonTerminalHash);
    insertNonTerminal("print", print, nonTerminalHash);
    insertNonTerminal("program", program, nonTerminalHash);
    insertNonTerminal("range_arrays", range_arrays, nonTerminalHash);
    insertNonTerminal("range_for_loop", range_for_loop, nonTerminalHash);
    insertNonTerminal("relationalOp", relationalOp, nonTerminalHash);
    insertNonTerminal("ret", ret, nonTerminalHash);
    insertNonTerminal("sign", sign, nonTerminalHash);
    insertNonTerminal("sign_for_loop", sign_for_loop, nonTerminalHash);
    insertNonTerminal("simpleStmt", simpleStmt, nonTerminalHash);
    insertNonTerminal("statement", statement, nonTerminalHash);
    insertNonTerminal("statements", statements, nonTerminalHash);
    insertNonTerminal("term", term, nonTerminalHash);
    insertNonTerminal("type", type, nonTerminalHash);
    insertNonTerminal("u", u, nonTerminalHash);
    insertNonTerminal("unary_op", unary_op, nonTerminalHash);
    insertNonTerminal("value", value, nonTerminalHash);
    insertNonTerminal("var", var, nonTerminalHash);
    insertNonTerminal("var_id_num", var_id_num, nonTerminalHash);
    insertNonTerminal("var_print", var_print, nonTerminalHash);
    insertNonTerminal("valueIDStmt", valueIDStmt, nonTerminalHash);
    insertNonTerminal("valueARRStmt", valueARRStmt, nonTerminalHash);
    insertNonTerminal("whichStmt", whichStmt, nonTerminalHash);
}
// int main(){
//     //lhs G1[NUM_OF_RULES];
//     //G1= generateGrammar();
//     generateGrammar();
//     for(int i=0;i<NUM_OF_RULES;i++){
//         printf("LHS_ID %d ", G[i].lhs_id);
//         // printf("Tail: %d", G[i].lastRHS->rhs_id);
//         rhs *temp = G[i].lastRHS;
//         while(temp != NULL){
//             printf("RHS_ID %d ", temp->rhs_id);
//             temp=temp->prevRHS;
//         }
//         printf("\n");
        
//     }
//     return 0;
// }


