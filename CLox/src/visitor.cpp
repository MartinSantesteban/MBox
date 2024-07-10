#include "./visitor.h"

string Visitor::visit(Expr& e){return "";}

string Visitor::visitBinary(Binary& e){return "";}

string Visitor::visitGrouping(Grouping& e){return "";}

string Visitor::visitLiteral(Literal& e){return "";}

string Visitor::visitUnary(Unary& e){return "";}


string Printer::visit(Expr& e){
       return e.accept(*this);
}

string Printer::visitBinary(Binary& e){
       string s = e.op->lexeme + " (" + (*e.left).accept(*this) + ") (" + (*e.right).accept(*this) + ")";    
       return s;
}

string Printer::visitGrouping(Grouping& e){
       string s = "group " + (*e.expression).accept(*this);
       return s;
}

string Printer::visitLiteral(Literal& e){
       string s = e.value->lexeme;
       return s;
}

string Printer::visitUnary(Unary& e){
       string s = e.op->lexeme + (*e.right).accept(*this);
       return s;
}
