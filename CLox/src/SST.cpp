#include "SST.h"

ExprStatement::ExprStatement(Expr* e){
    this->expression = e;
}

PrintStatement::PrintStatement(Expr* e){
    this->print_expression = e;
}