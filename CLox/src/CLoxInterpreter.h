#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "./AST.h"
#include "./SST.h"

class Expr;
class Binary;
class Grouping;
class Literal;
class Unary;

class Stmt;
class ExprStmt;
class PrintStmt;

class CLoxInterpreter{
public:      
       void printFormatedInterpretation(Expr& e);
       any interpret(Expr& e);
       any interpretBinary(Binary& e);
       any interpretGrouping(Grouping& e);
       any interpretLiteral(Literal& e);
       any interpretUnary(Unary& e);

       void interpretProgram(vector<Stmt*> ps);
       void interpretStmt(Stmt& s);
       void interpretExprStmt(ExprStmt& es);
       void interpretPrintStmt(PrintStmt& ps);
};

#endif
