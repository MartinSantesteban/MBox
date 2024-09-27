# Target : dependencies <- las dependencies al final son otras reglas, no tienen pq llamarse como archivos. Cuando pones los .cpp, en realidad no hacen nada.
# <tab> commands to make target
# Cuando usas make Target, se encarga make de que todas las dependencias esten up to date.

CC=g++
CFLAGS= -c -g -Wall -Wno-return-type
BINDIR=./bin
SRCDIR=./src
TSTDIR=./testing

clean: 
	rm -rf $(BINDIR)/*

test_all: test_MBoxLexer test_AST_Visitors test_AST_Expressions test_MBoxParser_Expressions test_MBoxParser_Statements test_MBoxParser_items test_MBoxInterpreter test_MBoxEnvironment test_MBox 

######################################################################################################################################################

test_MBoxLexer: MBoxLexer.o token.o enums_and_maps.o test_MBoxLexer.o
	$(CC) -o $(BINDIR)/test_MBoxLexer $(BINDIR)/token.o $(BINDIR)/MBoxLexer.o $(BINDIR)/enums_and_maps.o $(BINDIR)/test_MBoxLexer.o
	$(BINDIR)/test_MBoxLexer

test_MBoxParser_Expressions: MBoxParser.o token.o enums_and_maps.o test_MBoxParser_Expressions.o AST.o SST.o visitor.o MBoxEnvironment.o MBoxInterpreter.o MBoxObject.o
	$(CC) -o $(BINDIR)/test_MBoxParser_Expressions $(BINDIR)/enums_and_maps.o $(BINDIR)/token.o $(BINDIR)/MBoxObject.o $(BINDIR)/AST.o $(BINDIR)/SST.o $(BINDIR)/visitor.o $(BINDIR)/MBoxInterpreter.o $(BINDIR)/MBoxParser.o $(BINDIR)/test_MBoxParser_Expressions.o $(BINDIR)/MBoxEnvironment.o
	$(BINDIR)/test_MBoxParser_Expressions

test_MBoxInterpreter: enums_and_maps.o token.o AST.o MBoxEnvironment.o MBoxInterpreter.o test_MBoxInterpreter.o SST.o MBoxObject.o 
	$(CC) -o $(BINDIR)/test_MBoxInterpreter $(BINDIR)/token.o $(BINDIR)/enums_and_maps.o $(BINDIR)/AST.o $(BINDIR)/SST.o $(BINDIR)/MBoxObject.o $(BINDIR)/MBoxEnvironment.o $(BINDIR)/MBoxInterpreter.o $(BINDIR)/test_MBoxInterpreter.o 
	$(BINDIR)/test_MBoxInterpreter

test_MBox: MBoxLexer.o token.o enums_and_maps.o MBox.o test_MBox.o AST.o SST.o MBoxParser.o MBoxEnvironment.o MBoxInterpreter.o MBoxObject.o
	$(CC) -o $(BINDIR)/test_MBox  $(BINDIR)/test_MBox.o $(BINDIR)/token.o $(BINDIR)/MBoxLexer.o $(BINDIR)/enums_and_maps.o $(BINDIR)/MBox.o $(BINDIR)/MBoxParser.o $(BINDIR)/AST.o $(BINDIR)/SST.o $(BINDIR)/MBoxObject.o $(BINDIR)/MBoxEnvironment.o $(BINDIR)/MBoxInterpreter.o 
	$(BINDIR)/test_MBox

test_AST_Expressions: test_AST_Expressions.o AST.o visitor.o token.o enums_and_maps.o MBoxEnvironment.o MBoxInterpreter.o MBoxObject.o SST.o
	$(CC) -o $(BINDIR)/test_AST_Expressions $(BINDIR)/test_AST_Expressions.o $(BINDIR)/MBoxObject.o $(BINDIR)/AST.o $(BINDIR)/visitor.o $(BINDIR)/token.o $(BINDIR)/enums_and_maps.o $(BINDIR)/SST.o $(BINDIR)/MBoxEnvironment.o $(BINDIR)/MBoxInterpreter.o 
	$(BINDIR)/test_AST_Expressions

test_AST_Visitors: test_AST_Visitors.o AST.o SST.o visitor.o token.o enums_and_maps.o MBoxEnvironment.o MBoxInterpreter.o MBoxObject.o
	$(CC) -o $(BINDIR)/test_AST_Visitors $(BINDIR)/test_AST_Visitors.o $(BINDIR)/AST.o $(BINDIR)/visitor.o $(BINDIR)/token.o $(BINDIR)/enums_and_maps.o $(BINDIR)/MBoxObject.o $(BINDIR)/SST.o $(BINDIR)/MBoxEnvironment.o $(BINDIR)/MBoxInterpreter.o
	$(BINDIR)/test_AST_Visitors

test_MBoxParser_Statements: test_MBoxParser_Statements.o SST.o token.o enums_and_maps.o AST.o MBoxEnvironment.o MBoxInterpreter.o MBoxParser.o visitor.o MBoxObject.o
	$(CC) -o $(BINDIR)/test_MBoxParser_Statements $(BINDIR)/enums_and_maps.o $(BINDIR)/token.o $(BINDIR)/MBoxObject.o $(BINDIR)/SST.o $(BINDIR)/AST.o $(BINDIR)/visitor.o $(BINDIR)/MBoxEnvironment.o $(BINDIR)/MBoxInterpreter.o $(BINDIR)/MBoxParser.o $(BINDIR)/test_MBoxParser_Statements.o 
	$(BINDIR)/test_MBoxParser_Statements

test_MBoxParser_items: test_MBoxParser_items.o SST.o token.o enums_and_maps.o AST.o MBoxEnvironment.o MBoxInterpreter.o MBoxParser.o visitor.o MBoxObject.o
	$(CC) -o $(BINDIR)/test_MBoxParser_items $(BINDIR)/enums_and_maps.o $(BINDIR)/token.o $(BINDIR)/MBoxObject.o $(BINDIR)/SST.o $(BINDIR)/AST.o $(BINDIR)/visitor.o $(BINDIR)/MBoxEnvironment.o $(BINDIR)/MBoxInterpreter.o $(BINDIR)/MBoxParser.o $(BINDIR)/test_MBoxParser_items.o 
	$(BINDIR)/test_MBoxParser_items

test_MBoxEnvironment: enums_and_maps.o MBoxObject.o MBoxEnvironment.o test_MBoxEnvironment.o 
	$(CC) -o $(BINDIR)/test_MBoxEnvironment $(BINDIR)/enums_and_maps.o $(BINDIR)/MBoxObject.o $(BINDIR)/MBoxEnvironment.o $(BINDIR)/test_MBoxEnvironment.o
	$(BINDIR)/test_MBoxEnvironment

binary: enums_and_maps.o token.o AST.o SST.o MBoxLexer.o MBoxParser.o MBoxEnvironment.o MBoxInterpreter.o MBox.o main.o MBoxObject.o
	$(CC) -o $(BINDIR)/MBoxMain $(BINDIR)/enums_and_maps.o $(BINDIR)/token.o $(BINDIR)/AST.o $(BINDIR)/MBoxLexer.o $(BINDIR)/MBoxParser.o $(BINDIR)/SST.o $(BINDIR)/MBoxObject.o $(BINDIR)/MBoxEnvironment.o $(BINDIR)/MBoxInterpreter.o $(BINDIR)/MBox.o $(BINDIR)/main.o 


######################################################################################################################################################

MBoxLexer.o: ./src/MBoxLexer.cpp    
	$(CC) $(CFLAGS) ./src/MBoxLexer.cpp -o $(BINDIR)/MBoxLexer.o

MBox.o: ./src/MBox.cpp
	$(CC) $(CFLAGS) ./src/MBox.cpp -o $(BINDIR)/MBox.o

token.o: ./src/token.cpp
	$(CC) $(CFLAGS) ./src/token.cpp -o $(BINDIR)/token.o 

enums_and_maps.o: ./src/enums_and_maps.cpp
	$(CC) $(CFLAGS) ./src/enums_and_maps.cpp -o $(BINDIR)/enums_and_maps.o 

test_MBoxLexer.o: ./testing/test_MBoxLexer.cpp
	$(CC) $(CFLAGS) ./testing/test_MBoxLexer.cpp -o $(BINDIR)/test_MBoxLexer.o

test_MBox.o: ./testing/test_MBox.cpp
	$(CC) $(CFLAGS) ./testing/test_MBox.cpp -o $(BINDIR)/test_MBox.o

test_AST_Expressions.o : ./testing/test_AST_Expressions.cpp
	$(CC) $(CFLAGS) ./testing/test_AST_Expressions.cpp -o $(BINDIR)/test_AST_Expressions.o

test_AST_Visitors.o : ./testing/test_AST_Visitors.cpp
	$(CC) $(CFLAGS) ./testing/test_AST_Visitors.cpp -o $(BINDIR)/test_AST_Visitors.o

AST.o: ./src/AST.cpp
	$(CC) $(CFLAGS) ./src/AST.cpp -o $(BINDIR)/AST.o

visitor.o: ./src/visitor.cpp
	$(CC) $(CFLAGS) ./src/visitor.cpp -o $(BINDIR)/visitor.o

MBoxParser.o: ./src/MBoxParser.cpp
	$(CC) $(CFLAGS) ./src/MBoxParser.cpp -o $(BINDIR)/MBoxParser.o

test_MBoxParser_Expressions.o: ./testing/test_MBoxParser_Expressions.cpp
	$(CC) $(CFLAGS) ./testing/test_MBoxParser_Expressions.cpp -o $(BINDIR)/test_MBoxParser_Expressions.o

MBoxInterpreter.o: ./src/MBoxInterpreter.cpp
	$(CC) $(CFLAGS) ./src/MBoxInterpreter.cpp -o $(BINDIR)/MBoxInterpreter.o

test_MBoxInterpreter.o: ./testing/test_MBoxInterpreter.cpp
	$(CC) $(CFLAGS) ./testing/test_MBoxInterpreter.cpp -o $(BINDIR)/test_MBoxInterpreter.o

main.o: ./main.cpp
	$(CC) $(CFLAGS) ./main.cpp -o $(BINDIR)/main.o
	
SST.o: ./src/SST.cpp
	$(CC) $(CFLAGS) ./src/SST.cpp -o $(BINDIR)/SST.o

test_MBoxParser_Statements.o: ./testing/test_MBoxParser_Statements.cpp
	$(CC) $(CFLAGS) ./testing/test_MBoxParser_Statements.cpp -o $(BINDIR)/test_MBoxParser_Statements.o

MBoxObject.o: ./src/MBoxObject.cpp
	$(CC) $(CFLAGS) ./src/MBoxObject.cpp -o $(BINDIR)/MBoxObject.o

test_MBoxParser_items.o: ./testing/test_MBoxParser_items.cpp
	$(CC) $(CFLAGS) ./testing/test_MBoxParser_items.cpp -o $(BINDIR)/test_MBoxParser_items.o

MBoxEnvironment.o: ./src/MBoxEnvironment.cpp
	$(CC) $(CFLAGS) ./src/MBoxEnvironment.cpp -o $(BINDIR)/MBoxEnvironment.o

test_MBoxEnvironment.o: ./testing/test_MBoxEnvironment.cpp
	$(CC) $(CFLAGS) ./testing/test_MBoxEnvironment.cpp -o $(BINDIR)/test_MBoxEnvironment.o
	
