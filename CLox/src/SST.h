#ifndef SST_H
#define SST_H

#include "AST.h"
#include "CLoxInterpreter.h"

class Expr;
class CLoxInterpreter;

class Stmt{
    public:
        virtual ~Stmt() = default;
        bool operator==(Stmt& right);
        bool operator!=(Stmt& right);
        virtual void accept(CLoxInterpreter& ci) = 0;
    private:
        virtual bool _equals(Stmt& s) = 0;
};

class ExprStmt : public Stmt{
    public:
        ExprStmt(Expr* e);
        Expr* expr;
        void accept(CLoxInterpreter& ci);
    private:
        bool _equals(Stmt& s);
};

class PrintStmt : public Stmt{
    public:
        PrintStmt(Expr* e);
        Expr* print_expr;
        void accept(CLoxInterpreter& ci);
    private:
        bool _equals(Stmt& s);
};

#endif