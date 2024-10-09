#ifndef MBOX_INTERPRETER_H
#define MBOX_INTERPRETER_H

#include "./MBoxEnvironment.h"
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
class RedefinitionStmt;

class MBoxObject;

class MBoxEnvironment;

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
              void interpretRedefinitionStmt(RedefinitionStmt& ids);

              MBoxObject* getVariableValue(string varName);
       private:
              set<MBoxObject*> objects;
              MBoxEnvironment environment;

};

#endif
