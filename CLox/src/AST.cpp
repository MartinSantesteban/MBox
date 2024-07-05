#include "./AST.h"

string Expr::accept(Visitor& v){
    return "Expr: Subclass responsability.";
}

Binary::Binary(Expr *left,Token *op,Expr *right){
    this->left = left;
    this->op = op;
    this->right = right;
}

string Binary::accept(Visitor& v){
    return v.visitBinary(*this);
}

Grouping::Grouping(Expr *expression){
    this->expression = expression;
}

string Grouping::accept(Visitor& v){
    return v.visitGrouping(*this);
}

Literal::Literal(Token* t){
        this->value = t->lexeme;
}

string Literal::accept(Visitor& v){
    return v.visitLiteral(*this);
}

Unary::Unary(Token *op,Expr *right){
    this->op = op;
    this->right = right;
}

string Unary::accept(Visitor& v){
    return v.visitUnary(*this);
}

