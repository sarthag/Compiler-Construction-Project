#include "computeFirstandFollow.h"

void findf1(lhs target){
    //printf("here %d\n", target.lhs_id);
    rhs *temp = target.firstRHS;
    if (temp->isTerminal == 1){
       
        f1[target.lhs_id][temp->rhs_id] = 1;
        f1Done[target.lhs_id] = 1;
    }
    else{
       // printf("nt %d\n", temp->rhs_id);
        if (f1Done[temp->rhs_id] == 0){
            //printf("here: required first not done\n");
            for(int i = 0; i < NUM_OF_RULES; i++){
                if(G[i].lhs_id == temp->rhs_id){                    
                    findf1(G[i]);;
                }
            }
        }
        for(int i = 0; i < NUM_OF_TERMINALS - 1; i++){
            if(f1[temp->rhs_id][i] == 1){
                f1[target.lhs_id][i] = f1[temp->rhs_id][i];
            }
        }
        rhs * temp2 = temp->nextRHS;
        //printf("epsilon: %d \n", f1[temp->rhs_id][NUM_OF_TERMINALS-1]);
        while (f1[temp->rhs_id][NUM_OF_TERMINALS - 1] == 1){
            if(temp2 != NULL){
                if(temp2->isTerminal == 1){
                    f1[target.lhs_id][temp2->rhs_id] = 1;
                    break;
                }
                //printf("here: first nt has epsilon: %d\n", temp2->rhs_id);
                if (f1Done[temp2->rhs_id] == 0){
                    for(int i = 0; i < NUM_OF_RULES; i++){
                        if(G[i].lhs_id == temp2->rhs_id){
                            findf1(G[i]);;
                        }
                    }
                }
                //printf("\nrule found\n\n");
                for(int i = 0; i < NUM_OF_TERMINALS - 1; i++){
                    if(f1[temp2->rhs_id][i] == 1){
                        //printf("here");
                        f1[target.lhs_id][i] = 1;
                    }
                }
                temp = temp2;
                temp2 = temp2->nextRHS;
            }
            else{
                //printf("\n\nadding epsilon \n\n");
                f1[target.lhs_id][NUM_OF_TERMINALS-1] = 1;
                break;
            }
        }
        f1Done[target.lhs_id] = 1;
    }
    //printf("rule ended: %d \n", target.lhs_id);
}


void findf2(lhs start, rhs *target, rhs *temp){
    if (target->isTerminal == 1){
        return;
    }
    if(temp == NULL){
        printf("Only rhs in rule %d\n", target->rhs_id);
        for(int i =0; i < NUM_OF_TERMINALS; i++){
            f2[target->rhs_id][i] = f2[start.lhs_id][i];
        }
        return; 
    }
    if (temp->isTerminal == 1){
        printf("terminal is next\n");
        f2[target->rhs_id][temp->rhs_id] = 1;
        return;
    }
    printf("nt isnext \n");
    for(int i =0; i < NUM_OF_TERMINALS - 1; i++){
        if (f1[temp->rhs_id][i] == 1){
            f2[target->rhs_id][i] = f1[temp->rhs_id][i];
        }
    }
    if(f1[temp->rhs_id][NUM_OF_TERMINALS - 1] == 0){
        return;
    }
    rhs *temp2 = temp->nextRHS;
    if(temp2 == NULL){
        for(int i =0; i < NUM_OF_TERMINALS; i++){
            if (f2[start.lhs_id][i] == 1)
            f2[target->rhs_id][i] = f2[start.lhs_id][i];
        }
        return; 
    }
    findf2(start, target, temp2);

}


void computef1andf2(){
    //lhs G1[NUM_OF_RULES];
    //G1= generateGrammar();
    for(int j = NUM_OF_RULES - 1; j >= 0; j--){
        findf1(G[j]);
    }

    // for (int j = 0; j < NUM_OF_NONTERMINALS; j++){
    //     printf("\n%d\n%d\n", j, f1Done[j]);

    //     for(int i = 0; i < NUM_OF_TERMINALS; i++){
    //         printf("%d", f1[j][i]);
    //     }
    // }

    f2[0][NUM_OF_TERMINALS - 2] = 1;

    for(int j = 0; j < NUM_OF_RULES; j++){
        rhs * target = G[j].firstRHS;
        printf("rule: %d\n", j);
        while (target != NULL)
        {
            rhs * temp = target->nextRHS;
            printf("rhs null? %d\n", temp == NULL);
            findf2(G[j], target, temp); 
            target = temp;
        }       
    }

    // for (int j = 0; j < NUM_OF_NONTERMINALS; j++){
    //     printf("\n");
    //     for(int i = 0; i < NUM_OF_TERMINALS; i++){
            
    //         printf("%d", f2[j][i]);
    //     }      
    // }
}

// void syncronization_set(){
//     token_key semicol = SEMICOL, bc = BC, sqbc = SQBC;

//     for(int i=0; i<=NUM_OF_NONTERMINALS; i++){
//         for(int j=0; j<=NUM_OF_TERMINALS; j++){
//             sync_set[i][j] = (j == semicol) || (j == bc) || (j == sqbc) || f1[i][j] || f2[i][j];
//         }
//     }
// }


// /*
// int main(){
//     bool f1[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
//     bool f1Done[NO_NON_TERMINALS];
//     for (int j = 0; j < 5; j++){
//         findf1(G[j]);
//     }
//     for(int i = 0; i < NO_TERMINALS; i++){
//         printf("%d ", f1[0][i]);
//     }
// }
// */

// int main(){
//     populate_grammar();
//     generateGrammar();
//     computef1andf2();
//     return 0;
// }


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

// void findf1(lhs target){
//     // printf("entering f1 %d\n", target.lhs_id);

//     rhs *temp = target.firstRHS;
//     // printf("TEMP asfaf: %d  Type: %d\n",temp ->rhs_id, temp ->isTerminal);
//     rhs* temp2;
//     //printf("TEMP RHS ID :%d \n",temp->rhs_id);
//     if (temp->isTerminal == 1){
//         //printf("LHS ID: %d ,RHS ID : %d",target.lhs_id, temp->rhs_id);
//         // if(temp->rhs_id == NUM_OF_TERMINALS - 1){          
//         //     temp2 = temp->nextRHS;
//         //     if(temp2 != NULL){           
//         //     int i = 0;
//         //     for(i; i < NUM_OF_RULES; i++){
//         //         if(temp2 == NULL){
//         //             printf("FAIL");
//         //         }
//         //         if(G[i].lhs_id == temp2->rhs_id){
//         //             break;
//         //         }
//         //     }
            
//         //     findf1(G[i]);
//         //     for(int i = 0; i < NUM_OF_TERMINALS; i++){
//         //         if (f1[temp->rhs_id][i] == 1)
//         //         f1[target.lhs_id][i] = f1[temp->rhs_id][i];
//         //         f1Done[target.lhs_id] = 1;
//         //     }
//         //     }
//         // }
//         f1[target.lhs_id][temp->rhs_id] = 1;
//         if(target.lhs_id == 2){
//             printf("\n \n is terminal, fucked here\n \n");
//         }
//         // printf("Index: %d\n",temp -> rhs_id);
//         f1Done[target.lhs_id] = 1;
//     }
//     else{
//         // printf("inside repeated f1 and lhs is %d \n", target.lhs_id);

//         if(target.lhs_id == 2){
//             printf("\n \n fucked here\n \n");
//         }
//         if (f1Done[temp->rhs_id] == 0){
            
//             for(int i = 0; i < NUM_OF_RULES; i++){
//                 if(G[i].lhs_id == temp->rhs_id){
//                     findf1(G[i]);
//                     // break;
//                 }
//             }
            
//         }
//         for(int i = 0; i < NUM_OF_TERMINALS - 1; i++){
//             if(f1[temp->rhs_id][i] == 1){
//                 printf("%d ", target.lhs_id);
//                 f1[target.lhs_id][i] = 1;
//                 if(target.lhs_id == 2){
//                     printf("\n \ncorrect + some bt fucked here \n \n");
//                 }
//             }
//         }
//         // if(target.f1RHS->nextRHS == NULL){
//         //     printf("NULL HAI BHAI");
//         //     // printf("temp ->rhs id :%d\n",target.f1RHS->nextRHS -> rhs_id);
//         // }
//         temp = temp->nextRHS;
//         while (temp != NULL && f1[temp->rhs_id][NUM_OF_TERMINALS-1] == 1){
//             // printf("Inside while loop\n");
//             // printf("temp ->rhs id :%d\n",target.f1RHS-> rhs_id);
             
//             // printf("TEMP IS TERMINAL: %d ",temp ->isTerminal);
//             // printf("temp ->rhs id :%d\n",target.f1RHS->nextRHS -> rhs_id);
//             if(temp != NULL){
//                 // printf("next rhs %d \n", temp->rhs_id);
//                 if (f1Done[temp->rhs_id] == 0){
//                     // printf("Inside while loop f1 done\n");
//                     for(int i = 0; i < NUM_OF_RULES; i++){
//                         if(G[i].lhs_id == temp->rhs_id){
//                             findf1(G[i]);
//                             // break;
//                         }
//                     }
            
//                 }
            
//             for(int i = 0; i < NUM_OF_TERMINALS - 1; i++){
//                 if(f1[temp->rhs_id][i] == 1){
//                     f1[target.lhs_id][i] = 1;
//                     if(target.lhs_id == 2){
//                         printf("\n \nmultiple nts fucked here\n \n");
//                     }
//                 }
//             }
//             temp = temp->nextRHS;
//             }
//             else{
//                 f1[target.lhs_id][NUM_OF_TERMINALS-1] = 1;
//                 break;
//             }
//         }
//     }
//     f1Done[target.lhs_id] = 1;
//     // printf("f1 of arr_n4: %d",Fi)
// }

// void findf2(lhs start, rhs *target, rhs *temp){
//     if (target->isTerminal == 1){
//         return;
//     }
//     if(temp == NULL){
//         // printf("Target RHS ID :%d \n",target ->rhs_id);
//         for(int i =0; i < NUM_OF_TERMINALS; i++){
//             f2[target->rhs_id][i] = f2[start.lhs_id][i];
//         }
//         return; 
//     }
//     if (temp->isTerminal == 1){
//         f2[target->rhs_id][temp->rhs_id] = 1;
//         return;
//     }
//     for(int i =0; i < NUM_OF_TERMINALS - 1; i++){
//         if (f1[temp->rhs_id][i] == 1){
//             f2[target->rhs_id][i] = 1;
//         }
//     }
//     if(f1[temp->rhs_id][NUM_OF_TERMINALS - 1] == 0){
//         return;
//     }
//     rhs *temp2 = temp->nextRHS;
//     if(temp2 == NULL){
//         for(int i =0; i < NUM_OF_TERMINALS; i++){
//             if (f2[start.lhs_id][i] == 1)
//             f2[target->rhs_id][i] = f2[start.lhs_id][i];
//         }
//         return; 
//     }
//     findf2(start, target, temp2);

// }


// void computef1andf2(){
//     //lhs G1[NUM_OF_RULES];
//     //G1= generateGrammar();
//     for(int i=0;i<NUM_OF_NONTERMINALS;i++){
//         f1Done[i]=0;
//     }
//     for(int j = NUM_OF_RULES - 1; j >= 0; j--){
//         //printf("printing rule no %d ", j);
//         //printf("%d \n", j);
//         findf1(G[j]);
//     }

//     for (int j = 0; j < NUM_OF_NONTERMINALS; j++){
        
//             //printf("\n%d\n%d\n", j, f1Done[j]);
        

//         for(int i = 0; i < NUM_OF_TERMINALS; i++){
//             //printf("%d", f1[j][i]);
//         }
//     }

//     f2[program][NUM_OF_TERMINALS - 1] = 1;

//     for(int j = 0; j < NUM_OF_RULES; j++){
//         rhs * target = G[j].firstRHS;
//         while (target != NULL)
//         {
//             rhs * temp = target->nextRHS;
//             findf2(G[j], target, temp); 
//             target = temp;
//         }       
//     }

// }

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
    printf("here \n");
    generateGrammar();
    printf("here \n");
    computef1andf2();
    printf("here \n");
    loadFirstFollow();
    printf("here \n");

    

    for(int i = 0; i < NUM_OF_NONTERMINALS; i++){
        for(int j = 0; j < NUM_OF_TERMINALS; j++){
            if(First[i][j] != f1[i][j]){
                printf("Fucked first %d\n", i);
                break;
            }
        }
    }


    int count = 0;
    int followList[] = {0, 1, 2, 5, 6, 7, 8, 10, 13, 15, 17, 20, 22, 24, 25, 28, 29, 31, 34, 35, 36, 37, 38, 39, 40, 42, 44, 45, 49, 53, 61, 63, 63, 64};

    for(int i = 0; i < NUM_OF_NONTERMINALS; i++){
        for(int j = 0; j < NUM_OF_TERMINALS; j++){
            if(Follow[i][j] == 0 && f2[i][j] == 1){
                printf("Fucked Follow %d\n", i);
                break;
            }
        }
    }

    // findf1(G[54]);

    // for(int i = 0; i < 1; i++){
    //     for(int j = 0; j < NUM_OF_TERMINALS; j++){
    //         printf("%d ", Follow[2][j]);
    //     }
    // }
    // printf("\n");
    // for(int i = 0; i < 1; i++){
    //     for(int j = 0; j < NUM_OF_TERMINALS; j++){
    //         printf("%d ", f2[2][j]);
    //     }
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
