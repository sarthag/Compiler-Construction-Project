stage2exe: parser.o driver.o grammarHash.o adt.o ll1_gram.o lexer.o keywordTable.o astadt.o ast.o symbolTableCopy.o
	gcc -o stage2exe parser.o driver.o grammarHash.o adt.o ll1_gram.o lexer.o keywordTable.o astadt.o ast.o symbolTableCopy.o
parser.o: parser.c 
	gcc -c parser.c
driver.o : driver.c
	gcc -c driver.c
grammarHash.o: grammarHash.c
	gcc -c grammarHash.c
adt.o: adt.c
	gcc -c adt.c
ll1_gram.o: ll1_gram.c 
	gcc -c ll1_gram.c
lexer.o: lexer.c 
	gcc -c lexer.c
keywordTable.o: keywordTable.c 
	gcc -c keywordTable.c
astadt.o: astadt.c 
	gcc -c astadt.c
ast.o: ast.c 
	gcc -c ast.c
symbolTableCopy.o: symbolTableCopy.c
	gcc -c symbolTableCopy.c
clean:
	rm -f *.o 
	rm stage2exe
