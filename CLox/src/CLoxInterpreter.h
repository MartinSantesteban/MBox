#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "./AST.h"

class Expr;
class Binary;
class Grouping;
class Literal;
class Unary;

class CLoxInterpreter{
public:      
       void printFormatedInterpretation(Expr& e);
       any interpret(Expr& e);
       any interpretBinary(Binary& e);
       any interpretGrouping(Grouping& e);
       any interpretLiteral(Literal& e);
       any interpretUnary(Unary& e);
};

#endif
