#include "./CLoxInterpreter.h"



any CLoxInterpreter::interpret(Expr& e){
    return e.accept(*this);
};

any CLoxInterpreter::interpretBinary(Binary& e){
    /*
    any left_value = this->interpret(*e.left);
    any right_value = this->interpret(*e.right);
    any op_tt = (*e.op).token_type;
    any res;
    if(left_value)
    switch (op_tt){
        case LESS:
            res = 
    }
    return left_value;
    */
    any res = 5;
    return res;
};

any CLoxInterpreter::interpretGrouping(Grouping& e){
    return this->interpret(*e.expression);
};

any CLoxInterpreter::interpretLiteral(Literal& e){
    tokenType tt  = (*e.value).token_type;
    string lexeme = (*e.value).lexeme;
    any res;
    switch (tt){
        case STRING: 
            res = lexeme;
            return res;
        case NUMBER: 
            res = (double) stoi(lexeme);
            return res;
        case TRUE:
            res = true;
            return res;
        case FALSE:
            res = false;
            return res;
        case NIL:
            res = 0; 
            return res;
        default:
            break;
    }
    // should be unreachable 
    throw invalid_argument("CLoxInterpreter :: Unsupported token type in Literal expression.");
};

any CLoxInterpreter::interpretUnary(Unary& e){
    tokenType op_tt  = (*e.op).token_type;
    int line = (*e.op).line;
    any right_value = (*this).interpret(*e.right);
    any res;
    switch(op_tt){
        case BANG:
            if(right_value.type() == typeid(true)){
                bool right_bool = any_cast<bool>(right_value);
                res = !right_bool;
                return res;
            }else{
                throw invalid_argument("CLoxInterpreter :: line " + to_string(line) + " -- Right value of unary expression does not support the BANG operator.");
            }
        case MINUS:
            if(right_value.type() == typeid((double) 1)){ //horrendo, mejorar
                double right_double = any_cast<double>(right_value);
                res = - right_double;
                return res;
            }else{
                throw invalid_argument("CLoxInterpreter :: line " + to_string(line) + " -- Right value of unary expression does not support the MINUS operator.");
            }
        default:
            break;
    }
    throw invalid_argument("CLoxInterpreter :: Unsupported token type in Unary expression.");
};

