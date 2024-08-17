#ifndef SST_H
#define SST_H

#include "AST.h"

class Statement{
    public:
        virtual ~Statement() = default;
};

class ExprStatement : public Statement{
    public:
        ExprStatement(Expr* e);
        Expr* expression;
};

class PrintStatement : public Statement{
    public:
        PrintStatement(Expr* e);
        Expr* print_expression;
};

#endif