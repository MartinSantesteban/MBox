#include "./AST.h"
#include <typeinfo>

string Expr::accept(Visitor& v){
    return "Expr: Subclass responsability.";
}

bool Expr::_equals(Expr& e){
    return typeid(*this) == typeid(e);
}

bool Expr::operator ==(Expr& e){
    return this->_equals(e);
}

bool Expr::operator !=(Expr& e){
    return !(this->_equals(e));
}

Binary::Binary(Expr *left,Token *op,Expr *right){
    this->left = left;
    this->op = op;
    this->right = right;
}

string Binary::accept(Visitor& v){
    return v.visitBinary(*this);
}

bool Binary::_equals(Expr& e){
    if(typeid(*this) != typeid(e)) return false;
    auto e_bin = static_cast<Binary &>(e);
    return *(this->left) == *(e_bin.left) &&
           *(this->right) == *(e_bin.right) &&
           *(this->op) == *(e_bin.op);
}

Grouping::Grouping(Expr *expression){
    this->expression = expression;
}

string Grouping::accept(Visitor& v){
    return v.visitGrouping(*this);
}

bool Grouping::_equals(Expr& e){
    if(typeid(*this) != typeid(e)) return false;
    auto e_grouping = static_cast<Grouping &>(e);
    return *(this->expression) == *(e_grouping.expression);
}

Literal::Literal(Token* t){
    this->value = t;
}

string Literal::accept(Visitor& v){
    return v.visitLiteral(*this);
}

bool Literal::_equals(Expr& e){
    if(typeid(*this) != typeid(e)) return false;     
    auto e_literal = dynamic_cast<Literal &>(e);
    return *(this->value) == *(e_literal.value);
}

Unary::Unary(Token *op,Expr *right){
    this->op = op;
    this->right = right;
}

string Unary::accept(Visitor& v){
    return v.visitUnary(*this);
}

bool Unary::_equals(Expr& e){
    if(typeid(*this) != typeid(e)) return false;
    auto e_unary = static_cast<Unary &>(e);
    return *(this->op) == *(e_unary.op) && *(this->right) == *(e_unary.right);
}

