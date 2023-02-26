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

FILE* readFile(char *filename){
    FILE *code = fopen(filename , "r");
    if(code == NULL) {
        printf("File Opening Error!\n");
        return NULL;
    }
    //initializing buffers and token linked list 
    memset(buffers.buffer1, 0, BUFFERSIZE+1);
    memset(buffers.buffer1, 0, BUFFERSIZE+1);
    tokenList.start = NULL;
    tokenList.end = NULL;
    tokenList.tokenCount = 0;

    eof = false;
    numChar = 0;
    line_no = 1;

    int buf_size1 = fread(buffers.buffer1, sizeof(char), BUFFERSIZE, code);
    buffers.buffer1[buf_size1] = '\0';
    begin = buffers.buffer1;    
    forward = buffers.buffer1;
    started = true;
    
    return code;
}


FILE* getStream(FILE *code){
    if (forward == buffers.buffer1 + BUFFERSIZE - 1) {
        int buf_size2 = fread(buffers.buffer2, sizeof(char), BUFFERSIZE, code);
        buffers.buffer2[buf_size2] = '\0';
        forward = buffers.buffer2;
    }

    else if (forward == buffers.buffer2 + BUFFERSIZE - 1) {\
        int buf_size2 = fread(buffers.buffer1, sizeof(char), BUFFERSIZE, code);
        buffers.buffer1[buf_size2] = '\0';
        forward = buffers.buffer1;
    }

    else {
        forward++;
    }

    return code;
}


char getNextChar(FILE* code) {
    char current = *forward;
    code = getStream(code);
    numChar++;
    forward++; // need to figure out buffer edge cases
    return current;
}


token* addTokenToList(){
    token* tk = (token*)malloc(sizeof(token));
    if(tokenList.start == NULL){
        tokenList.start = tk;
    }
    else{
        tokenList.end -> next = tk;
    }

    return tokenList.end = tk;
}


void resetLexeme(){
    begin = forward;
    numChar = 0;
}


void retract(int n) {
    if(forward >= buffers.buffer1 && forward <= buffers.buffer1 + BUFFERSIZE) {
        if(forward - buffers.buffer1 < n) {
            n -= forward - buffers.buffer1;
            forward = buffers.buffer2 + BUFFERSIZE - n;
        }

        else {
            forward -= n;
        }
    }

    else if(forward >= buffers.buffer2 && forward <= buffers.buffer2 + BUFFERSIZE) {
        if(forward - buffers.buffer2 < n) {
            n -= forward - buffers.buffer2;
            forward = buffers.buffer1 + BUFFERSIZE - n;
        }

        else {
            forward -= n;
        }
    }
    numChar -= n;
}

char *getLexeme() {
    char *lex = (char *) malloc((numChar + 1) * sizeof(char));
    int c = 0;
    char *curr = begin;
    bool case_1 = begin >= buffers.buffer1 && begin <= buffers.buffer1 + BUFFERSIZE;
    bool case_2 = forward >= buffers.buffer1 && forward <= buffers.buffer1 + BUFFERSIZE;
    bool case_3 = begin >= buffers.buffer2 && begin <= buffers.buffer2 + BUFFERSIZE;
    bool case_4 = forward >= buffers.buffer1 && forward <= buffers.buffer1 + BUFFERSIZE;

    if((case_1 && case_2) || (case_3 && case_4)) {
        while(curr < forward) {
            lex[c] = *curr;
            c++;
            curr++;
        }
    }

    else if(case_1 && case_4) {
        while(curr < buffers.buffer1 + BUFFERSIZE) {
            lex[c] = *curr;
            c++;
            curr++;
        }
        curr = buffers.buffer2;
        while(curr < forward) {
            lex[c] = *curr;
            c++;
            curr++;
        }
    }

    else {
        while(curr < buffers.buffer2 + BUFFERSIZE) {
            lex[c] = *curr;
            c++;
            curr++;
        }
        curr = buffers.buffer1;
        while(curr < forward) {
            lex[c] = *curr;
            c++;
            curr++;
        }
    }

    return lex;
}

token_key tokenizeIDorKeyword(char* lexeme, ktElement keywordTable[]){
    token_key key = getTokenFromKT(lexeme, keyword_table);
    if(key == -1){
        return ID; 
    }
    else{
        return key;
    }
}



token getNextToken(FILE *code) {
    state = 1;
    err = 0;
    token t;
    char c;
    

    while (state >= 1) {
        c = getNextChar(code);
        switch (state)
        {
        case 1:
            t = *addTokenToList();
            if(c >= '0' && c <= '9') {
                state = 2;
            } // shreyas check

            else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
                state = 8;
            } // shreyas has figured it out

            else if(c == '.') {
                state = 9;
            }

            else if(c == ' '){
                state = 11;
            } // done 

            else if(c == '\\'){
                state = 12;
            } // done 

            else if(c == '*'){
                state = 15;
            } // done

            else if(c == ':'){
                state = 19;
            } // done

            else if(c == '>'){
                state = 21;
            } // done

            else if(c == '<'){
                state = 25;
            } // done

            else if(c == '!'){
                state = 29;
            } // done

            else if(c == '='){
                state = 31;
            } // done

            else if(c == '-'){
                state = 33;
            } //  done 

            else if(c == '+'){
                state = 34;
            } // done 

            else if(c == ','){
                state = 35; 
            } // done 

            else if(c == ';'){
                state = 36;
            } // done 

            else if(c == '/'){
                state = 37; 
            } // done 

            else if(c == '('){
                state = 38;
            } // done 

            else if(c == ')'){
                state = 39; 
            } // done

            else if(c == '['){
                state = 40;
            } // done 

            else if(c == ']'){
                state = 41; 
            } // done 

            break;

        case 2:
            if(c >= '0' && c <= '9') {
                state = 2;
            }
            else if(c == '.') {
                state = 3;
            }
            else { // should be else if(c == ' ');
                retract(1);
                t.tid = NUM;
                t.num = atoi(getLexeme());
                t.line_no = line_no; 
                resetLexeme();
                state = 1; 
            }
            // Shreyas check
            break;

        case 3:
            if (c >= '0' && c <= '9') {
                state = 4;
            }
            else if (c == '.') {
                retract(2);
                t.tid = NUM;
                t.num = atoi(getLexeme());
                t.line_no = line_no; 
                resetLexeme();
                state = 1; 
            }
            else {
                err = -3;
                state = 0; 
                // Error state -3 (Invalid character after num .)
                // Shreyas check
                //this is fine
            }
            break;

        case 4:
            if(c >= '0' && c <= '9') {
                state = 4;
            }
            else if(c == 'E' || c == 'e') {
                state = 5;
            }
            else {
                t.tid = RNUM;
                t.rnum = atof(getLexeme());
                t.line_no = line_no; 
                resetLexeme();
                state = 1; 
            }
            break;

        case 5:
            if (c == '+' || c == '-') {
                state = 6;
            }
            else if(c >= '0' && c <= '9') {
                state = 7;
            }
            else {
                retract(1);
                t.tid = RNUM;
                t.rnum = atof(getLexeme());
                t.line_no = line_no; 
                resetLexeme();
                state = 1; 
            }
            break;
        
        case 6:
            if(c >= '0' && c <= '9') {
                state = 7;
            }
            else {
                err = -3;
                state = 0;
                // Error state -3 (Invalid character after e+/-)
            }
            break;

        case 7:
            if (c >= '0' && c <= '9') {
                state = 7;
            }
            else {
                t.tid = RNUM;
                t.rnum = atof(getLexeme());
                t.line_no = line_no; 
                resetLexeme();
                state = 1; 
            }
            break;

        case 8: //final state
            if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
                state = 8;
            }
            else{
                retract(1);
                char* lexeme = getLexeme();
                token_key tkn = tokenizeIDorKeyword(lexeme, keyword_table);
                t.tid = tkn;
                t.lexeme = lexeme;
                t.line_no = line_no;
                resetLexeme();
                state = 1; 
            }
            //shrayes has finished making it
            break;
        
        case 9:
            if(c == '.') {
                state = 10;
            }
            else {
                err = -3; 
                state = 0; 
                // Error state -3 (Invalid character after .)
            }
            break;

        case 10:
            t.tid = RANGEOP;
            t.lexeme = getLexeme(); 
            t.line_no = line_no; 
            resetLexeme();
            state = 1; 
            break;

        case 11: //final state
            if(c == ' '){
                state = 11;
            }
            else{
                state = 1;
            }
            break;

        case 12:
            if(c == 't'){
                state = 13;
            }
            else if(c == 'n'){
                state = 14;
            }
            else{
                err = -2; 
                state = 0;
                //error state -2 (\ with invalid character)
            }
            break;

        case 13: //final state
            state = 1;
            break;

        case 14: // final state
            line_no++;
            state = 1;
            break;

        case 15:
            if(c == '*') {
                state = 16;
            }
            else {
                retract(1);
                t.tid = MUL;
                t.lexeme = getLexeme(); 
                t.line_no = line_no; 
                resetLexeme();
                state = 1; 
            }
            break;
        
        case 16:
            if(c == '*') {
                state = 17;
            }
            else if(c == EOF) {
                err = -1; 
                state = 0;
                // Error state -1 (comment mark not closed)
            }
            else if(c == '\\') {
                state = 42;
            }
            else {
                state = 16;
            }
        
        case 42:
            if(c == 'n') {
                line_no++;
            }
            state = 16;
            break;

        case 17:
            if(c == '*') {
                state = 18;
            }
            else {
                state = 16;
            }
            break;
        
        case 18:
            t.tid = COMMENTMARK;
            t.lexeme = getLexeme(); 
            t.line_no = line_no; 
            resetLexeme();
            state = 1; 
            break;

        case 19:
            if(c == '='){
                state = 20; 
            }

            else{
                retract(1);
                t.tid = COLON;
                t.lexeme = getLexeme(); 
                t.line_no = line_no; 
                resetLexeme();
                state = 1; 
                break;
            }
            break; 

        case 20:
            t.tid = ASSIGNOP; 
            t.lexeme = getLexeme(); 
            t.line_no = line_no;
            resetLexeme(); 
            state = 1; 
            break; 

        case 21:
            if(c == '='){
                state = 22;
            }
            else if(c == '>'){
                state = 23;
            }
            else{
                retract(1);
                t.tid = GT;
                t.lexeme = getLexeme(); 
                t.line_no = line_no; 
                resetLexeme();
                state = 1; 
                //retract and tokenize;
            }
            break;

        case 22:
            t.tid = GE;
            t.lexeme = getLexeme();
            t.line_no = line_no;
            state = 1;
            break;

        case 23:
            if(c == '>'){
                state = 24;
            }
            else{
                retract(1);
                t.tid = ENDDEF;
                t.lexeme = getLexeme(); 
                t.line_no = line_no; 
                resetLexeme();
                state = 1; 
                //retract and tokenize
            }
            break;

        case 24:
            t.tid = DRIVERENDDEF;
            t.lexeme = getLexeme();
            t.line_no = line_no;
            state = 1;
            break;

        case 25:
            if(c == '='){
                state = 28;
            }
            else if(c == '<'){
                state = 26;
            }
            else{
                retract(1);
                t.tid = LT;
                t.lexeme = getLexeme(); 
                t.line_no = line_no; 
                resetLexeme();
                state = 1; 
                //retract and tokenize;
            }
            break;

        case 26:
            if(c == '<'){
                state = 27;
            }
            else{
                retract(1);
                t.tid = DEF;
                t.lexeme = getLexeme(); 
                t.line_no = line_no; 
                resetLexeme();
                state = 1; 
            }
            break;

        case 27:
            t.tid = DRIVERDEF;
            t.lexeme = getLexeme();
            t.line_no = line_no;
            state = 1;
            break;

        case 28:
            t.tid = LE;
            t.lexeme = getLexeme();
            t.line_no = line_no;
            state = 1;
            break;

        case 29: 
            if(c == '='){
                state = 30;
            }
            else{ 
                err = -3;
                state = 0;
                // Error state -3 (invalid character after !)
            }
            break;
        
        case 30: 
            t.tid = NE;
            t.lexeme = getLexeme();
            t.line_no = line_no;
            resetLexeme();
            state = 1; 
            break;

        case 31: 
            if(c == '='){
                state = 32;
            }
            else{ 
                err = -3;
                state = 0;
                // Error state -3 (Invalid character after =)
            }
            break;
        
        case 32: 
            t.tid = EQ;
            t.lexeme = getLexeme();
            t.line_no = line_no;
            resetLexeme();
            state = 1; 
            break;

        case 33: 
            t.tid = MINUS;
            t.lexeme = getLexeme();
            t.line_no = line_no;
            resetLexeme();
            state = 1; 
            break;

        case 34: 
            t.tid = PLUS;
            t.lexeme = getLexeme();
            t.line_no = line_no;
            resetLexeme();
            state = 1; 
            break;

        case 35: 
            t.tid = COMMA;
            t.lexeme = getLexeme();
            t.line_no = line_no;
            resetLexeme();
            state = 1; 
            break;

        case 36: 
            t.tid = SEMICOL;
            t.lexeme = getLexeme();
            t.line_no = line_no;
            resetLexeme();
            state = 1; 
            break;

        case 37: 
            t.tid = DIV;
            t.lexeme = getLexeme();
            t.line_no = line_no;
            resetLexeme();
            state = 1; 
            break;

        case 38: 
            t.tid = BO;
            t.lexeme = getLexeme();
            t.line_no = line_no;
            resetLexeme();
            state = 1; 
            break;

        case 39: 
            t.tid = BC;
            t.lexeme = getLexeme();
            t.line_no = line_no;
            resetLexeme();
            state = 1; 
            break;

        case 40: 
            t.tid = SQBO;
            t.lexeme = getLexeme();
            t.line_no = line_no;
            resetLexeme();
            state = 1; 
            break;

        case 41: 
            t.tid = SQBC;
            t.lexeme = getLexeme();
            t.line_no = line_no;
            resetLexeme();
            state = 1; 
            break;

        default:
            err = -3; 
            state = 0; 
            break;
        }
    }


    if(err < 0) {
        state = -1;
        switch (err)
        {
        case -1:
            printf("ERROR at line %d: comment mark not closed\n", line_no);
            break;
        case -2:
            printf("ERROR at line %d: invaild escape sequence\n", line_no);
            break;
        case -3:
            printf("ERROR at line %d: invalid character sequence]n", line_no);
            break;
        default:
            break;
        }
    }
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


