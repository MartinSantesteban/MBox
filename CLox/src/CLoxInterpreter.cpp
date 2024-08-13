#include "./CLoxInterpreter.h"

any CLoxInterpreter::interpret(Expr& e){
    return e.accept(*this);
};

any CLoxInterpreter::interpretBinary(Binary& e){
    any a = 4;
    return a;
};

any CLoxInterpreter::interpretGrouping(Grouping& e){
    any a = 4;
    return a;
};

any CLoxInterpreter::interpretLiteral(Literal& e){
    any a = 4;
    return a;
};

any CLoxInterpreter::interpretUnary(Unary& e){
    any a = 4;
    return a;
};