run: parser.o computeFirstandFollow.c adt.o ll1_gram.o lexer.o keywordTable.o
	gcc -o exe parser.o computeFirstandFollow.o adt.o ll1_gram.o lexer.o keywordTable.o
	./exe 
parser.o: parser.c 
	gcc -c parser.c
computeFirstandFollow.o: computeFirstandFollow.c 
	gcc -c computeFirstandFollow.c
adt.o: adt.c
	gcc -c adt.c
ll1_gram.o: ll1_gram.c 
	gcc -c ll1_gram.c
lexer.o: lexer.c 
	gcc -c lexer.c
keywordTable.o: keywordTable.c 
	gcc -c keywordTable.c
clean:
	rm -f *.o runParserCode
