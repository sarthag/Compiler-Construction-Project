#include "ll1_gram.h"
#include "parser.h"

bool isTerm(char* str){
    //terminal
    if(str[0] >= 65 && str[0]<= 90){
        return 1;
    }
    return 0;
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

void populate_parse_table(){
    //populate the table with -1 
    for(int i=0;i<NUM_OF_NONTERMINALS;i++){
        for(int j=0;j< NUM_OF_TERMINALS;j++){
            parse_table[i][j]=-1;
        }
    }
    for(int i=0;i<NUM_OF_RULES;i++){
        int eps= getTokenFromTTable("EPSILON", terminalHash);
        if(G[i].firstRHS->isTerminal==1){
            //if it's a TERMINAL
            if(G[i].firstRHS->rhs_id!=eps){
                printf("Rule is terminal without eps %d \n", i+1);
                parse_table[G[i].lhs_id][G[i].firstRHS->rhs_id]=i;
            }
            else{
                printf("Rule is terminal with eps %d \n", i+1);
                //epsilon - calculate follow
                for(int k=0;k<NUM_OF_TERMINALS;k++){
                    if(Follow[G[i].lhs_id][k]==1){
                        parse_table[G[i].lhs_id][k] = i;
                    }
                }
            }
            
        }
        else{
            //is a nt
            printf("Rule is non term %d\n", i+1);
            for(int j = 0; j < NUM_OF_TERMINALS-1; j++){
                //printf("first of non terminal %d ", First[G[i].firstRHS->rhs_id][j]);
                if (First[G[i].firstRHS->rhs_id][j] == 1){
                    // if(parse_table[G[i].lhs_id][j] != -1){
                    //     printf("First except epsilon Old: %d , New: %d\n",parse_table[G[i].lhs_id][j]+1,i+1);
                    // }
                    //printf("lhs id is %d ", G[i].lhs_id);
                    parse_table[G[i].lhs_id][j] = i;
                }
            }

            if(First[G[i].firstRHS->rhs_id][eps]==1){
                //if the first set contains epsilon populate with follow
                for(int k=0;k<NUM_OF_TERMINALS-1;k++){
                    if(Follow[G[i].lhs_id][k]==1){
                        // if(parse_table[G[i].lhs_id][k] != -1){
                        //     printf("Epsilon in first \tOld: %d , New: %d\n",parse_table[G[i].lhs_id][k]+1,i+1);
                        // }
                        parse_table[G[i].lhs_id][k] = i;
                    }
                }
            }
        }
        
    }
    int ctr = 0;
    // for(int i=0;i<NUM_OF_NONTERMINALS;i++){
    //     for(int j=0;j<NUM_OF_TERMINALS;j++){
    //         if(parse_table[i][j] == 4){
    //             printf("%d ",parse_table[i][j]);
    //         }
    //         else{
    //             printf(" ");
    //         }
            
            
    //     }
    //     // printf("\n");
    // }
}


// void findFirst(lhs target){
//     // printf("entering first %d\n", target.lhs_id);

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
            
//         //     findFirst(G[i]);
//         //     for(int i = 0; i < NUM_OF_TERMINALS; i++){
//         //         if (First[temp->rhs_id][i] == 1)
//         //         First[target.lhs_id][i] = First[temp->rhs_id][i];
//         //         firstDone[target.lhs_id] = 1;
//         //     }
//         //     }
//         // }
//         First[target.lhs_id][temp->rhs_id] = 1;
//         if(target.lhs_id == 2){
//             printf("\n \n is terminal, fucked here\n \n");
//         }
//         // printf("Index: %d\n",temp -> rhs_id);
//         firstDone[target.lhs_id] = 1;
//     }
//     else{
//         // printf("inside repeated first and lhs is %d \n", target.lhs_id);

//         if(target.lhs_id == 2){
//             printf("\n \n fucked here\n \n");
//         }
//         if (firstDone[temp->rhs_id] == 0){
            
//             for(int i = 0; i < NUM_OF_RULES; i++){
//                 if(G[i].lhs_id == temp->rhs_id){
//                     findFirst(G[i]);
//                     // break;
//                 }
//             }
            
//         }
//         for(int i = 0; i < NUM_OF_TERMINALS - 1; i++){
//             if(First[temp->rhs_id][i] == 1){
//                 printf("%d ", target.lhs_id);
//                 First[target.lhs_id][i] = 1;
//                 if(target.lhs_id == 2){
//                     printf("\n \ncorrect + some bt fucked here \n \n");
//                 }
//             }
//         }
//         // if(target.firstRHS->nextRHS == NULL){
//         //     printf("NULL HAI BHAI");
//         //     // printf("temp ->rhs id :%d\n",target.firstRHS->nextRHS -> rhs_id);
//         // }
//         temp = temp->nextRHS;
//         while (temp != NULL && First[temp->rhs_id][NUM_OF_TERMINALS-1] == 1){
//             // printf("Inside while loop\n");
//             // printf("temp ->rhs id :%d\n",target.firstRHS-> rhs_id);
             
//             // printf("TEMP IS TERMINAL: %d ",temp ->isTerminal);
//             // printf("temp ->rhs id :%d\n",target.firstRHS->nextRHS -> rhs_id);
//             if(temp != NULL){
//                 // printf("next rhs %d \n", temp->rhs_id);
//                 if (firstDone[temp->rhs_id] == 0){
//                     // printf("Inside while loop first done\n");
//                     for(int i = 0; i < NUM_OF_RULES; i++){
//                         if(G[i].lhs_id == temp->rhs_id){
//                             findFirst(G[i]);
//                             // break;
//                         }
//                     }
            
//                 }
            
//             for(int i = 0; i < NUM_OF_TERMINALS - 1; i++){
//                 if(First[temp->rhs_id][i] == 1){
//                     First[target.lhs_id][i] = 1;
//                     if(target.lhs_id == 2){
//                         printf("\n \nmultiple nts fucked here\n \n");
//                     }
//                 }
//             }
//             temp = temp->nextRHS;
//             }
//             else{
//                 First[target.lhs_id][NUM_OF_TERMINALS-1] = 1;
//                 break;
//             }
//         }
//     }
//     firstDone[target.lhs_id] = 1;
//     // printf("First of arr_n4: %d",Fi)
// }

// void findFollow(lhs start, rhs *target, rhs *temp){
//     if (target->isTerminal == 1){
//         return;
//     }
//     if(temp == NULL){
//         // printf("Target RHS ID :%d \n",target ->rhs_id);
//         for(int i =0; i < NUM_OF_TERMINALS; i++){
//             Follow[target->rhs_id][i] = Follow[start.lhs_id][i];
//         }
//         return; 
//     }
//     if (temp->isTerminal == 1){
//         Follow[target->rhs_id][temp->rhs_id] = 1;
//         return;
//     }
//     for(int i =0; i < NUM_OF_TERMINALS - 1; i++){
//         if (First[temp->rhs_id][i] == 1){
//             Follow[target->rhs_id][i] = 1;
//         }
//     }
//     if(First[temp->rhs_id][NUM_OF_TERMINALS - 1] == 0){
//         return;
//     }
//     rhs *temp2 = temp->nextRHS;
//     if(temp2 == NULL){
//         for(int i =0; i < NUM_OF_TERMINALS; i++){
//             if (Follow[start.lhs_id][i] == 1)
//             Follow[target->rhs_id][i] = Follow[start.lhs_id][i];
//         }
//         return; 
//     }
//     findFollow(start, target, temp2);

// }


// void computeFirstandFollow(){
//     //lhs G1[NUM_OF_RULES];
//     //G1= generateGrammar();
//     for(int i=0;i<NUM_OF_NONTERMINALS;i++){
//         firstDone[i]=0;
//     }
//     for(int j = NUM_OF_RULES - 1; j >= 0; j--){
//         //printf("printing rule no %d ", j);
//         printf("%d \n", j);
//         findFirst(G[j]);
//     }

//     for (int j = 0; j < NUM_OF_NONTERMINALS; j++){
        
//             printf("\n%d\n%d\n", j, firstDone[j]);
        

//         for(int i = 0; i < NUM_OF_TERMINALS; i++){
//             printf("%d", First[j][i]);
//         }
//     }

//     Follow[program][NUM_OF_TERMINALS - 1] = 1;

//     for(int j = 0; j < NUM_OF_RULES; j++){
//         rhs * target = G[j].firstRHS;
//         while (target != NULL)
//         {
//             rhs * temp = target->nextRHS;
//             findFollow(G[j], target, temp); 
//             target = temp;
//         }       
//     }

//     for (int j = 0; j < NUM_OF_NONTERMINALS; j++){
//         int sum = 0;
        
//         for(int i = 0; i < NUM_OF_TERMINALS; i++){
//             sum+= First[j][i];
//             // printf("%d ", First[j][i]);
//             // printf("%d", Follow[j][i]);
//             // if(j == arr_N5){
//             //     sum+= Follow[j][i];
//             //     printf("%d ", Follow[j][i]);
//             // }
//             // if(j == arr_N4 && First[j][i] == 1){
//             //      printf("%d ", i);
//             // }
//             // if(j == arr_N4 && First[arr_N4][i] == 1){
//             //     printf("%d ",i);
//             // }

            
            
//         } 
//         //printf("\n"); 
//         // if (sum == 0){
//         //     printf("\n Row No: %d \n",j);
//         // }    
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
    printf("Printing for term \n ");
    for(int i=0;i<NUM_OF_TERMINALS;i++){
            printf("%d ", First[63][i]);
    }
    
    // print the contents of the array
    // printf("First Array\n");
    // for (int i = 0; i < NUM_OF_NONTERMINALS; i++) {
    //     for (int j = 0; j < NUM_OF_TERMINALS; j++) {
    //         printf("%d ", First[i][j]);
    //     }
    //     printf("\n");
    // }
    
    // close the file
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
    
    // print the contents of the array
    // printf("Follow Array:\n");
    // for (int i = 0; i < NUM_OF_NONTERMINALS; i++) {
    //     for (int j = 0; j < NUM_OF_TERMINALS; j++) {
    //         printf("%d ", Follow[i][j]);
    //     }
    //     printf("\n");
    // }
    
    // close the file
    fclose(h);
}

void printGrammar(){
    for(int i = 0; i < NUM_OF_RULES; i++){
        rhs * temp = G[i].firstRHS;
        printf("Line no: %d :- ",i+1);
        printf("%d ", G[i].lhs_id);
        while(temp != NULL){
            printf("%d ",temp->rhs_id);
            temp = temp -> nextRHS;
        }
        printf("\n");
    }
}

int main(){
    populate_grammar();
    generateGrammar();
    loadFirstFollow();
    // computeFirstandFollow();
    populate_parse_table();
    //         printf("Arithematic\n");
    // for(int i = 0; i < NUM_OF_TERMINALS; i++){

    //     printf(" %d ", First[2][i]);
    // }
    //  printf("Anyterm\n");
    // for(int i = 0; i < NUM_OF_TERMINALS; i++){
       
    //     printf(" %d ", First[1][i]);
    // }
    bool arr[NUM_OF_RULES] = {0};
    for(int i = 0 ; i < NUM_OF_NONTERMINALS ; i++){
        // printf("NTNO: %d \n", i);
        for(int j = 0 ; j < NUM_OF_TERMINALS ;j++){
            if(arr[parse_table[i][j]]==0){
                arr[parse_table[i][j]]=1;
            }
        }
    }
    printf("\n Sus numbers\n");
    for(int i = 0 ; i < NUM_OF_RULES ; i++){
        if(arr[i] == 0){
            printf("%d ", i);
        }
    }
    printf("\ndone with parse table");
    return 0;
}



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


