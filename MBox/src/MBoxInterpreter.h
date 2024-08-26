#ifndef MBOX_INTERPRETER_H
#define MBOX_INTERPRETER_H

#include "./MBoxObject.h"
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

class MBoxObject;

class MBoxInterpreter{
       public:      
              void printFormatedInterpretation(Expr& e);

              MBoxObject* interpret(Expr& e);
              MBoxObject* interpretBinary(Binary& e);
              MBoxObject* interpretGrouping(Grouping& e);
              MBoxObject* interpretLiteral(Literal& e);
              MBoxObject* interpretUnary(Unary& e);

              void interpretProgram(vector<Stmt*> ps);
              void interpretStmt(Stmt& s);
              void interpretExprStmt(ExprStmt& es);
              void interpretPrintStmt(PrintStmt& ps);
       private:
              vector<MBoxObject*> objects;
};

#endif
