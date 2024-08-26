#ifndef VISITOR_H
#define VISITOR_H

#include "./AST.h"

// Forward declarations
class Expr;
class Binary;
class Grouping;
class Literal;
class Unary;


class Visitor{
public:
       virtual string visit(Expr& e);
       virtual string visitBinary(Binary& e);
       virtual string visitGrouping(Grouping& e);
       virtual string visitLiteral(Literal& e);
       virtual string visitUnary(Unary& e);
};

class Printer : public Visitor{
public:      
       string visit(Expr& e);
       string visitBinary(Binary& e);
       string visitGrouping(Grouping& e);
       string visitLiteral(Literal& e);
       string visitUnary(Unary& e);
};

#endif

// ver como meter un visitor con otro return type