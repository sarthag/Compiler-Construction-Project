runParserCode: createParseTable.o ll1_gram.o
	gcc -o runParserCode ll1_gram.o createParseTable.o
	./runParserCode
createParseTable.o: createParseTable.c parser.h parserDef.h
	gcc -c createParseTable.c
ll1_gram.o: ll1_gram.c parser.h parserDef.h
	gcc -c ll1_gram.c
clean: 
	rm -f *.o runParserCode 