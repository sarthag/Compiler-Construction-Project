#include "computeFirstandFollow.h"

void findFirst(lhs target){
    //printf("here %d\n", target.lhs_id);
    rhs *temp = target.firstRHS;
    if (temp->isTerminal == 1){
       
        First[target.lhs_id][temp->rhs_id] = 1;
        firstDone[target.lhs_id] = 1;
    }
    else{
       // printf("nt %d\n", temp->rhs_id);
        if (firstDone[temp->rhs_id] == 0){
            //printf("here: required first not done\n");
            for(int i = 0; i < NUM_OF_RULES; i++){
                if(G[i].lhs_id == temp->rhs_id){                    
                    findFirst(G[i]);;
                }
            }
        }
        for(int i = 0; i < NUM_OF_TERMINALS - 1; i++){
            if(First[temp->rhs_id][i] == 1){
                First[target.lhs_id][i] = First[temp->rhs_id][i];
            }
        }
        rhs * temp2 = temp->nextRHS;
        //printf("epsilon: %d \n", First[temp->rhs_id][NUM_OF_TERMINALS-1]);
        while (First[temp->rhs_id][NUM_OF_TERMINALS - 1] == 1){
            if(temp2 != NULL){
                if(temp2->isTerminal == 1){
                    First[target.lhs_id][temp2->rhs_id] = 1;
                    break;
                }
                //printf("here: first nt has epsilon: %d\n", temp2->rhs_id);
                if (firstDone[temp2->rhs_id] == 0){
                    for(int i = 0; i < NUM_OF_RULES; i++){
                        if(G[i].lhs_id == temp2->rhs_id){
                            findFirst(G[i]);;
                        }
                    }
                }
                //printf("\nrule found\n\n");
                for(int i = 0; i < NUM_OF_TERMINALS - 1; i++){
                    if(First[temp2->rhs_id][i] == 1){
                        //printf("here");
                        First[target.lhs_id][i] = 1;
                    }
                }
                temp = temp2;
                temp2 = temp2->nextRHS;
            }
            else{
                //printf("\n\nadding epsilon \n\n");
                First[target.lhs_id][NUM_OF_TERMINALS-1] = 1;
                break;
            }
        }
        firstDone[target.lhs_id] = 1;
    }
    //printf("rule ended: %d \n", target.lhs_id);
}


void findFollow(lhs start, rhs *target, rhs *temp, int rule){
    if (target->isTerminal == 1){
        return;
    }
    if(temp == NULL){
        //printf("last rhs in rule %d\n", target->rhs_id);
        for(int i =0; i < NUM_OF_TERMINALS - 2; i++){
            if(Follow[start.lhs_id][i] == 1){
                Follow[target->rhs_id][i] = Follow[start.lhs_id][i];
            }
        }
        if (start.lhs_id == G[0].lhs_id || start.lhs_id == G[0].lastRHS->rhs_id || start.lhs_id == G[0].lastRHS->prevRHS->rhs_id){
            Follow[target->rhs_id][NUM_OF_TERMINALS - 2] = 1;
        }
        return; 
    }
    if (temp->isTerminal == 1){
        //printf("terminal is next\n");
        Follow[target->rhs_id][temp->rhs_id] = 1;
        return;
    }
    //printf("nt isnext \n");
    for(int i =0; i < NUM_OF_TERMINALS - 2; i++){
        if (First[temp->rhs_id][i] == 1){
            Follow[target->rhs_id][i] = First[temp->rhs_id][i];
        }
    }
    if(First[temp->rhs_id][NUM_OF_TERMINALS - 1] == 0){
        return;
    }
    rhs *temp2 = temp->nextRHS;
    if(temp2 == NULL){
        for(int i =0; i < NUM_OF_TERMINALS - 2; i++){
            if (Follow[start.lhs_id][i] == 1){
                Follow[target->rhs_id][i] = Follow[start.lhs_id][i];
            }
            if (start.lhs_id == 53){
                Follow[target->rhs_id][NUM_OF_TERMINALS - 2] = 1;
            }
        }
        
        if (start.lhs_id == G[0].lhs_id || start.lhs_id == G[0].lastRHS->rhs_id || start.lhs_id == G[0].lastRHS->prevRHS->rhs_id){
            Follow[target->rhs_id][NUM_OF_TERMINALS - 2] = 1;
        }
        return; 
    }
    findFollow(start, target, temp2, rule);

}



void computeFirstandFollow(){
    for(int j = NUM_OF_RULES - 1; j >= 0; j--){
        findFirst(G[j]);
    }

    
    Follow[53][NUM_OF_TERMINALS - 2] = 1;

    for(int j = 0; j < NUM_OF_RULES; j++){
        rhs * target = G[j].firstRHS;
        //printf("rule: %d\n", j);
        while (target != NULL)
        {
            rhs * temp = target->nextRHS;
            findFollow(G[j], target, temp, j); 
            target = temp;
        }       
    }

    for(int j =0; j < NUM_OF_RULES; j++){
        if(flag[j] == 0){
            rhs * target = G[j].firstRHS;
            //printf("rule: %d\n", j);
            while (target != NULL)
            {
                rhs * temp = target->nextRHS;
                //printf("rhs null? %d\n", temp == NULL);
                findFollow(G[j], target, temp, j); 
                target = temp;
            } 
        }
    }

}

void generateGrammar(){
    FILE *fp = fopen("grammar.txt", "r");
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
                //printf("getting from table for str %s %d \n ",str, getTokenFromNTTable(str, nonTerminalHash));
                G[rule_no].lhs_id = getTokenFromNTTable(str, nonTerminalHash);
                //printf("%d ", G[rule_no].lhs_id);
                G[rule_no].firstRHS = NULL;   
            }
            else {
                //printf("Line %s \n", str);
                rhs *new_rhs = (rhs *)malloc(sizeof(rhs));
                new_rhs->isTerminal = isTerm(str);
                if(new_rhs->isTerminal==0){
                    new_rhs->rhs_id = getTokenFromNTTable(str, nonTerminalHash);
                }
                else{
                    new_rhs->rhs_id = getTokenFromTTable(str, terminalHash);
                }
                if(new_rhs->rhs_id==-1){
                    printf("||%s||", str);
                }
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
    insertTerminal("GT", GT, terminalHash);
    insertTerminal("ID", ID, terminalHash);
    insertTerminal("IN", IN, terminalHash);
    insertTerminal("INPUT", INPUT, terminalHash);
    insertTerminal("INTEGER", INTEGER, terminalHash);
    insertTerminal("LE", LE, terminalHash);
    insertTerminal("LT", LT, terminalHash);
    insertTerminal("MINUS", MINUS, terminalHash);
    insertTerminal("MODULE", MODULE, terminalHash);
    insertTerminal("MUL", MUL, terminalHash);
    insertTerminal("NE", NE, terminalHash);
    insertTerminal("NUM", NUM, terminalHash);
    insertTerminal("OF", OF, terminalHash);
    insertTerminal("OR", OR, terminalHash);
    insertTerminal("PARAMETERS", PARAMETERS, terminalHash);
    insertTerminal("PLUS", PLUS, terminalHash);
    insertTerminal("PRINT", PRINT, terminalHash);
    insertTerminal("PROGRAM", PROGRAM, terminalHash);
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
    insertNonTerminal("actualParaList", actualParaList, nonTerminalHash);
    insertNonTerminal("anyTerm", anyTerm, nonTerminalHash);
    insertNonTerminal("arithmeticExpr", arithmeticExpr, nonTerminalHash);
    insertNonTerminal("arithmeticOrBooleanExpr", arithmeticOrBooleanExpr, nonTerminalHash);
    insertNonTerminal("arrExpr", arrExpr, nonTerminalHash);
    insertNonTerminal("arrFactor", arrFactor, nonTerminalHash);
    insertNonTerminal("arrTerm", arrTerm, nonTerminalHash);
    insertNonTerminal("arr_N4", arr_N4, nonTerminalHash);
    insertNonTerminal("arr_N5", arr_N5, nonTerminalHash);
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
    insertNonTerminal("n7", n7, nonTerminalHash);
    insertNonTerminal("new_NT", new_NT, nonTerminalHash);
    insertNonTerminal("new_index", new_index, nonTerminalHash);
    insertNonTerminal("new_index_for_loop", new_index_for_loop, nonTerminalHash);
    insertNonTerminal("op1", op1, nonTerminalHash);
    insertNonTerminal("op2", op2, nonTerminalHash);
    insertNonTerminal("optional", optional, nonTerminalHash);
    insertNonTerminal("otherModules", otherModules, nonTerminalHash);
    insertNonTerminal("output_plist1", output_plist1, nonTerminalHash);
    insertNonTerminal("output_plist2", output_plist2, nonTerminalHash);
    insertNonTerminal("p1", p1, nonTerminalHash);
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
    //insertNonTerminal("var", var, nonTerminalHash);
    insertNonTerminal("var_id_num", var_id_num, nonTerminalHash);
    insertNonTerminal("var_print", var_print, nonTerminalHash);
    insertNonTerminal("valueIDStmt", valueIDStmt, nonTerminalHash);
    insertNonTerminal("valueARRStmt", valueARRStmt, nonTerminalHash);
    insertNonTerminal("whichStmt", whichStmt, nonTerminalHash);
}

bool isTerm(char* str){
    //terminal
    if(str[0] >= 65 && str[0]<= 90){
        return 1;
    }
    return 0;
}

void loadFirstFollow() {
    FILE *g = fopen("firstArr.txt", "r");
    
    // read each line of the file and store its contents in the array
    for (int i = 0; i < NUM_OF_NONTERMINALS; i++) {
        char line[256];
        fgets(line, sizeof(line), g);
        
        // split the line into an array of integers
        char *token;
        int j = 0;
        token = strtok(line, ",");
        while (token != NULL) {
            First[i][j] = atoi(token);
            j++;
            token = strtok(NULL, ",");
        }
    }
    
    fclose(g);

    FILE *h = fopen("followArr.txt", "r");
    
    // read each line of the file and store its contents in the array
    for (int i = 0; i < NUM_OF_NONTERMINALS; i++) {
        char line[256];
        fgets(line, sizeof(line), h);
        
        // split the line into an array of integers
        char *token;
        int j = 0;
        token = strtok(line, ",");
        while (token != NULL) {
            Follow[i][j] = atoi(token);
            j++;
            token = strtok(NULL, ",");
        }
    }

    fclose(h);
}

int main(){
    
    populate_grammar();
//    printf("here \n");
    generateGrammar();
//    printf("here \n");
    computeFirstandFollow();
//    printf("here \n");
    loadFirstFollow();
//    printf("here \n");

    

    for(int i = 0; i < NUM_OF_NONTERMINALS; i++){
        for(int j = 0; j < NUM_OF_TERMINALS; j++){
            if(First[i][j] != First[i][j]){
                printf("Fucked first %d\n", i);
                break;
            }
        }
    }


    // int count = 0;
    // int followList[] = {0, 53};

    for(int i = 0; i < NUM_OF_NONTERMINALS; i++){
        for(int j = 0; j < NUM_OF_TERMINALS; j++){
            if(Follow[i][j] != Follow[i][j]){
                printf("Fucked follow %d\n", i);
                //count += 1;
                break;
            }
        }
    }
    // printf("count Follow fucked %d\n", count);
    // // findf1(G[54]);

    // for(int k = 0; k < 3; k++){
    //     printf("%d \n", k);
    //     for(int j = 0; j < NUM_OF_TERMINALS; j++){
    //         printf("%d ", Follow[followList[k]][j]);
    //     }
    //     printf("\n");
    //     for(int j = 0; j < NUM_OF_TERMINALS; j++){
    //         printf("%d ", f2[followList[k]][j]);
    //     }
    //     printf("\n");
    // }
    // for (int i = 0; i < 40; i++){
    //     printf("\n here \n");
    //     printf("%d\n", followList[i]);
    //     printf("\n here \n");
    //     for(int j = 0; j < NUM_OF_TERMINALS; j++){
    //         printf("%d ", Follow[followList[i]][j]);
    //     }
    //     printf("\n");
    //     for(int j = 0; j < NUM_OF_TERMINALS; j++){
    //         printf("%d ", f2[followList[i]][j]);
    //     }
    //     printf("\n");
    // }

    printf("DOne");
    // printf("%d \n \n", G[54].firstRHS->nextRHS->rhs_id);

}
