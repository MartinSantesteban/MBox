#ifndef SST_H
#define SST_H

#include "AST.h"
#include "MBoxInterpreter.h"

class Expr;
class MBoxInterpreter;

class Stmt{
    public:
        virtual ~Stmt() = default;
        bool operator==(Stmt& right);
        bool operator!=(Stmt& right);
        virtual void accept(MBoxInterpreter& i) = 0;
    private:
        virtual bool _equals(Stmt& s) = 0;
};

class ExprStmt : public Stmt{
    public:
        ExprStmt(Expr* e);
        Expr* expr;
        void accept(MBoxInterpreter& i);
    private:
        bool _equals(Stmt& s);
};

class PrintStmt : public Stmt{
    public:
        PrintStmt(Expr* e);
        Expr* print_expr;
        void accept(MBoxInterpreter& i);
    private:
        bool _equals(Stmt& s);
};

class ItemDeclStmt : public Stmt{
    public:
        ItemDeclStmt(Token* identifier_tkn, Expr* e);
        Token* identifier_tkn;
        Expr* value_expr;
        void accept(MBoxInterpreter& i);
        string itemName();
    private:
        bool _equals(Stmt& s);
};

class RedefinitionStmt : public Stmt{
    public:
        RedefinitionStmt(Token* identifier_tkn, Expr* e);
        Token* identifier_tkn;
        Expr* value_expr;
        void accept(MBoxInterpreter& i);
        string itemName();
    private:
        bool _equals(Stmt& s);
};

#endif

// al ser clases bastante anemicas no hago privados los miembros. Debería hacerlos const!!!