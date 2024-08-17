#ifndef SST_H
#define SST_H

#include "AST.h"

class Stmt{
    public:
        virtual ~Stmt() = default;
        bool operator==(Stmt& right);
        bool operator!=(Stmt& right);
    private:
        virtual bool _equals(Stmt& s) = 0;
};

class ExprStmt : public Stmt{
    public:
        ExprStmt(Expr* e);
        Expr* expr;
    private:
        bool _equals(Stmt& s);
};

class PrintStmt : public Stmt{
    public:
        PrintStmt(Expr* e);
        Expr* print_expr;
    private:
        bool _equals(Stmt& s);
};

#endif