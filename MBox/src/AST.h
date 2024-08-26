#ifndef AST_H
#define AST_H

#include "./token.h"
#include "./visitor.h"
#include "./MBoxObject.h"
#include "./MBoxInterpreter.h"

class Visitor;
class MBoxInterpreter;

class Expr{ 
    public:
        virtual string accept(Visitor& v) = 0;
        virtual MBoxObject* accept(MBoxInterpreter& v) = 0;
        virtual ~Expr() = default;
        bool operator ==(Expr& e);
        bool operator !=(Expr& e);
    private: 
        virtual bool _equals(Expr& e);
};

class Binary : public Expr{
    public:
        Binary(Expr *left,Token *op,Expr *right);
        Expr* left;
        Token* op;
        Expr* right;
        string accept(Visitor& v);
        MBoxObject* accept(MBoxInterpreter& v);
    private: 
        bool _equals(Expr& e);
};

class Grouping : public Expr{
    public:
        Grouping(Expr *expression);
        Expr* expression;
        string accept(Visitor& v);
        MBoxObject* accept(MBoxInterpreter& v);
    private: 
        bool _equals(Expr& e);
};

class Literal : public Expr{
    public:
        Literal(Token* t);
        Token* value;
        string accept(Visitor& v);
        MBoxObject* accept(MBoxInterpreter& v);
    private: 
        bool _equals(Expr& e);
};

class Unary : public Expr{
    public:
        Unary(Token *op,Expr *right);
        Token* op;
        Expr* right;
        string accept(Visitor& v);
        MBoxObject* accept(MBoxInterpreter& v);
    private: 
        bool _equals(Expr& e);
};

#endif


