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

void ExprStmt::accept(MBoxInterpreter& i){
    return i.interpretExprStmt(*this);
}

PrintStmt::PrintStmt(Expr* e){
    this->print_expr = e;
}

bool PrintStmt::_equals(Stmt& s){
    if(typeid(*this) != typeid(s)) return false;
    PrintStmt& ps = static_cast<PrintStmt &>(s);
    return *(this->print_expr) == *(ps.print_expr);
}

void PrintStmt::accept(MBoxInterpreter& i){
    return i.interpretPrintStmt(*this);
}

ItemDeclStmt::ItemDeclStmt(Token* identifier_tkn, Expr* e){
    this->identifier_tkn = identifier_tkn;
    this->value_expr = e;
}

void ItemDeclStmt::accept(MBoxInterpreter& i){
    return i.interpretItemDeclStmt(*this);
}

bool ItemDeclStmt::_equals(Stmt& s){
    if(typeid(*this) != typeid(s)) return false;
    ItemDeclStmt& ids = static_cast<ItemDeclStmt &>(s);
    return *(this->identifier_tkn) == *(ids.identifier_tkn) &&
           *(this->value_expr) == *(ids.value_expr);
}

string ItemDeclStmt::itemName(){
    return this->identifier_tkn->lexeme;
}