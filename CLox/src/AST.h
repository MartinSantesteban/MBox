#ifndef AST_H
#define AST_H

#include "./token.h"
#include "./visitor.h"

class Visitor;

class Expr{ 
    public:
        virtual string accept(Visitor& v);
};

class Binary : public Expr{
    public:
        Binary(Expr *left,Token *op,Expr *right);
        Expr* left;
        Token* op;
        Expr* right;
        string accept(Visitor& v);
};

class Grouping : public Expr{
    public:
        Grouping(Expr *expression);
        Expr* expression;
        string accept(Visitor& v);
};

class Literal : public Expr{
    public:
        Literal(Token* t);
        string value;
        string accept(Visitor& v);
};

class Unary : public Expr{
    public:
        Unary(Token *op,Expr *right);
        Token* op;
        Expr* right;
        string accept(Visitor& v);
};

#endif


