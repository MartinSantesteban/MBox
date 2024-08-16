# Target : dependencies <- las dependencies al final son otras reglas, no tienen pq llamarse como archivos. Cuando pones los .cpp, en realidad no hacen nada.
# <tab> commands to make target
# Cuando usas make Target, se encarga make de que todas las dependencias esten up to date.

CC=g++
CFLAGS= -c -g -Wall

clean: 
	rm -rf ./bin/*

test_all: test_CLoxLexer test_AST_Visitors test_AST_Expressions test_CLoxParser test_CLoxInterpreter test_CLox

######################################################################################################################################################

test_CLoxLexer: CLoxLexer.o token.o enums_and_maps.o test_CLoxLexer.o
	$(CC) -o ./bin/test_CLoxLexer ./bin/token.o ./bin/CLoxLexer.o ./bin/enums_and_maps.o ./bin/test_CLoxLexer.o
	./bin/test_CLoxLexer

test_CLoxParser: CLoxParser.o token.o enums_and_maps.o test_CLoxParser.o AST.o visitor.o CLoxInterpreter.o
	$(CC) -o ./bin/test_CLoxParser ./bin/AST.o ./bin/visitor.o ./bin/CLoxParser.o ./bin/token.o ./bin/enums_and_maps.o ./bin/test_CLoxParser.o ./bin/CLoxInterpreter.o
	./bin/test_CLoxParser

test_CLoxInterpreter: enums_and_maps.o token.o AST.o CLoxInterpreter.o test_CLoxInterpreter.o
	$(CC) -o ./bin/test_CLoxInterpreter ./bin/token.o ./bin/enums_and_maps.o ./bin/AST.o ./bin/CLoxInterpreter.o ./bin/test_CLoxInterpreter.o
	./bin/test_CLoxInterpreter

test_CLox: CLoxLexer.o token.o enums_and_maps.o CLox.o test_CLox.o AST.o CLoxParser.o CLoxInterpreter.o
	$(CC) -o ./bin/test_CLox  ./bin/test_CLox.o ./bin/token.o ./bin/CLoxLexer.o ./bin/enums_and_maps.o ./bin/CLox.o ./bin/CLoxParser.o ./bin/AST.o ./bin/CLoxInterpreter.o
	./bin/test_CLox

test_AST_Expressions: test_AST_Expressions.o AST.o visitor.o token.o enums_and_maps.o CLoxInterpreter.o
	$(CC) -o ./bin/test_AST_Expressions ./bin/test_AST_Expressions.o ./bin/AST.o ./bin/visitor.o ./bin/token.o ./bin/enums_and_maps.o ./bin/CLoxInterpreter.o
	./bin/test_AST_Expressions

test_AST_Visitors: test_AST_Visitors.o AST.o visitor.o token.o enums_and_maps.o CLoxInterpreter.o
	$(CC) -o ./bin/test_AST_Visitors ./bin/test_AST_Visitors.o ./bin/AST.o ./bin/visitor.o ./bin/token.o ./bin/enums_and_maps.o ./bin/CLoxInterpreter.o
	./bin/test_AST_Visitors

binary: enums_and_maps.o token.o AST.o CLoxLexer.o CLoxParser.o CLoxInterpreter.o CLox.o main.o
	$(CC) -o ./bin/CLoxMain ./bin/enums_and_maps.o ./bin/token.o ./bin/AST.o ./bin/CLoxLexer.o ./bin/CLoxParser.o ./bin/CLoxInterpreter.o ./bin/CLox.o ./bin/main.o

######################################################################################################################################################

CLoxLexer.o: ./src/CLoxLexer.cpp    
	$(CC) $(CFLAGS) ./src/CLoxLexer.cpp -o ./bin/CLoxLexer.o

CLox.o: ./src/CLox.cpp
	$(CC) $(CFLAGS) ./src/CLox.cpp -o ./bin/CLox.o

token.o: ./src/token.cpp
	$(CC) $(CFLAGS) ./src/token.cpp -o ./bin/token.o 

enums_and_maps.o: ./src/enums_and_maps.cpp
	$(CC) $(CFLAGS) ./src/enums_and_maps.cpp -o ./bin/enums_and_maps.o 

test_CLoxLexer.o: ./testing/test_CLoxLexer.cpp
	$(CC) $(CFLAGS) ./testing/test_CLoxLexer.cpp -o ./bin/test_CLoxLexer.o

test_CLox.o: ./testing/test_CLox.cpp
	$(CC) $(CFLAGS) ./testing/test_CLox.cpp -o ./bin/test_CLox.o

test_AST_Expressions.o : ./testing/test_AST_Expressions.cpp
	$(CC) $(CFLAGS) ./testing/test_AST_Expressions.cpp -o ./bin/test_AST_Expressions.o

test_AST_Visitors.o : ./testing/test_AST_Visitors.cpp
	$(CC) $(CFLAGS) ./testing/test_AST_Visitors.cpp -o ./bin/test_AST_Visitors.o

AST.o: ./src/AST.cpp
	$(CC) $(CFLAGS) ./src/AST.cpp -o ./bin/AST.o

visitor.o: ./src/visitor.cpp
	$(CC) $(CFLAGS) ./src/visitor.cpp -o ./bin/visitor.o

CLoxParser.o: ./src/CLoxParser.cpp
	$(CC) $(CFLAGS) ./src/CLoxParser.cpp -o ./bin/CLoxParser.o

test_CLoxParser.o: ./testing/test_CLoxParser.cpp
	$(CC) $(CFLAGS) ./testing/test_CLoxParser.cpp -o ./bin/test_CLoxParser.o

CLoxInterpreter.o: ./src/CLoxInterpreter.cpp
	$(CC) $(CFLAGS) ./src/CLoxInterpreter.cpp -o ./bin/CLoxInterpreter.o

test_CLoxInterpreter.o: ./testing/test_CLoxInterpreter.cpp
	$(CC) $(CFLAGS) ./testing/test_CLoxInterpreter.cpp -o ./bin/test_CLoxInterpreter.o

main.o: ./main.cpp
	$(CC) $(CFLAGS) ./main.cpp -o ./bin/main.o

	