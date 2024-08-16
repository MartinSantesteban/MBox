#include "./CLoxInterpreter.h"

map<tokenType, function<any(string)>>  literalClosures = {{STRING, [](string lexeme){return lexeme;}},
                                                          {NUMBER, [](string lexeme){return (double) stoi(lexeme);}},
                                                          {TRUE,   [](string lexeme){return true;}},
                                                          {FALSE,  [](string lexeme){return false;}},
                                                          {NIL,    [](string lexeme){return 0;}}};

map<tokenType, function<any(double, double)>> binaryDoubleClosures = {{LESS,    [](double left, double right){return left < right;}},
                                                                {LESS_EQUAL,    [](double left, double right){return left <= right;}},
                                                                {GREATER,       [](double left, double right){return left > right;}},
                                                                {GREATER_EQUAL, [](double left, double right){return left >= right;}},
                                                                {PLUS,          [](double left, double right){return left + right;}},
                                                                {MINUS,         [](double left, double right){return left - right;}},
                                                                {STAR,          [](double left, double right){return left * right;}},
                                                                {SLASH,         [](double left, double right){return left / right;}}};

template <typename T>
bool any_equality(any left_value, any right_value){
    T left_T = any_cast<T>(left_value);
    T right_T = any_cast<T>(right_value);
    return left_T == right_T;
}

template <typename A,typename B, typename C>
bool equality(any left_value, any right_value, tokenType equality_op){
    bool res;
    if(right_value.type() != left_value.type()) res = false;
    if(right_value.type() == typeid(A)) res = any_equality<A>(left_value, right_value);
    if(right_value.type() == typeid(B)) res = any_equality<B>(left_value, right_value);
    if(right_value.type() == typeid(C)) res = any_equality<C>(left_value, right_value);
    return (equality_op == EQUAL_EQUAL)? res : !res;
}

template <typename T>
bool operands_are_of_type(any left_value, any right_value){
    return right_value.type() == typeid(T) && left_value.type() == typeid(T);
}

void CLoxInterpreter::printFormatedInterpretation(Expr& e){
    any res = this->interpret(e);
    if(res.type() == typeid(bool)) cout << ((any_cast<bool>(res) == 1)? "True" : "False") << endl;
    if(res.type() == typeid(double)) cout << any_cast<double>(res) << endl;
    if(res.type() == typeid(string)) cout << any_cast<string>(res) << endl;
}

any CLoxInterpreter::interpret(Expr& e){
    return e.accept(*this);
};

any CLoxInterpreter::interpretGrouping(Grouping& e){
    return this->interpret(*e.expression);
};

any CLoxInterpreter::interpretBinary(Binary& e){
    any left_value = this->interpret(*e.left);
    any right_value = this->interpret(*e.right);
    tokenType op_tt = (*e.op).token_type;
    any res;
    if(op_tt == EQUAL_EQUAL || op_tt == BANG_EQUAL){
        res = (equality<string, bool, double>(left_value, right_value, op_tt));
        return res;
    }
    if(operands_are_of_type<double>(left_value, right_value)){
        double right_double = any_cast<double>(right_value);
        double left_double = any_cast<double>(left_value);    
        res = binaryDoubleClosures[op_tt](left_double, right_double);
        return res;
    }
    if(operands_are_of_type<string>(left_value, right_value)){
        string right_string = any_cast<string>(right_value);
        string left_string = any_cast<string>(left_value);
        left_string.pop_back();
        res = left_string + right_string.erase(0,1);
        return res;
    }
    //should be unreachable
    throw invalid_argument("CLoxInterpreter :: Unsupported token type in Binary expression.");
};

any CLoxInterpreter::interpretLiteral(Literal& e){
    tokenType tt  = (*e.value).token_type;
    string lexeme = (*e.value).lexeme;
    any res = literalClosures[tt](lexeme);
    return res;
};

any CLoxInterpreter::interpretUnary(Unary& e){
    tokenType op_tt  = (*e.op).token_type;
    int line = (*e.op).line;
    any right_value = (*this).interpret(*e.right);
    if(right_value.type() == typeid(true) && op_tt == BANG){
        bool right_bool = any_cast<bool>(right_value);
        return !(right_bool);
    }
    if(right_value.type() == typeid(double) && op_tt == MINUS){ 
        double right_double = any_cast<double>(right_value);
        return (-1) * right_double;
    }
    //should be unreachable
    throw invalid_argument("CLoxInterpreter :: line " + to_string(line) + " -- Right value of unary expression does not support the " + tokenTypeString[op_tt] + " operator.");
};

