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
class ItemDeclStmt;

class MBoxObject;

class MBoxInterpreter{
       public:      
              ~MBoxInterpreter();
              void printFormatedInterpretation(Expr& e);

              MBoxObject* interpretExpr(Expr& e);
              MBoxObject* interpretBinary(Binary& e);
              MBoxObject* interpretGrouping(Grouping& e);
              MBoxObject* interpretLiteral(Literal& e);
              MBoxObject* interpretUnary(Unary& e);

              void interpretProgram(vector<Stmt*> ps);
              void interpretStmt(Stmt& s);
              void interpretExprStmt(ExprStmt& es);
              void interpretPrintStmt(PrintStmt& ps);
              void interpretItemDeclStmt(ItemDeclStmt& ids);
       private:
              set<MBoxObject*> objects;
};

#endif
