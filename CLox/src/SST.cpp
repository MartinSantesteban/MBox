#include "SST.h"

bool Stmt::operator ==(Stmt& right){
    return this->_equals(right);
}

bool Stmt::operator !=(Stmt& right){
    return !(this->_equals(right));
}

ExprStmt::ExprStmt(Expr* e){
    this->expr = e;
}

bool ExprStmt::_equals(Stmt& s){
    if(typeid(*this) != typeid(s)) return false;
    ExprStmt& e = static_cast<ExprStmt&>(s);
    return *(this->expr) == *(e.expr);
}

void ExprStmt::accept(CLoxInterpreter& ci){
    return ci.interpretExprStmt(*this);
}

PrintStmt::PrintStmt(Expr* e){
    this->print_expr = e;
}

bool PrintStmt::_equals(Stmt& s){
    if(typeid(*this) != typeid(s)) return false;
    PrintStmt& ps = static_cast<PrintStmt &>(s);
    return *(this->print_expr) == *(ps.print_expr);
}

void PrintStmt::accept(CLoxInterpreter& ci){
    return ci.interpretPrintStmt(*this);
}
