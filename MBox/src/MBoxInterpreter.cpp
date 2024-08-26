#include "./MBoxInterpreter.h"

map<tokenType, function<MBoxObject*(string)>>  literalClosures = {{STRING, [](string lexeme){return new MBoxString(lexeme);}},
                                                                 {NUMBER,  [](string lexeme){return new MBoxNumber((double) stoi(lexeme));}},
                                                                 {TRUE,    [](string lexeme){return new MBoxBoolean(true);}},
                                                                 {FALSE,   [](string lexeme){return new MBoxBoolean(false);}},
                                                                 {NIL,     [](string lexeme){return new MBoxNil();}}};

map<tokenType,function<MBoxObject*(MBoxObject* right)>> unaryCLosures = {{BANG,  [](MBoxObject* right){return (*right).handleBang();}},
                                                                          {MINUS, [](MBoxObject* right){return (*right).handleMinus();}}};

map<tokenType, function<MBoxObject*(MBoxObject* left, MBoxObject* right)>>  binaryClossures = {
                                                                /*{EQUAL_EQUAL,   [](MBoxObject* left, MBoxObject* right){return left->handleEq(right);}},
                                                                {BANG_EQUAL,    [](MBoxObject* left, MBoxObject* right){return left->handelNEq(right);}},*/
                                                                {LESS,          [](MBoxObject* left, MBoxObject* right){return left->handleLess(right);}},
                                                                {LESS_EQUAL,    [](MBoxObject* left, MBoxObject* right){return left->handleLessEq(right);}},
                                                                {GREATER,       [](MBoxObject* left, MBoxObject* right){return left->handleGreater(right);}},
                                                                {GREATER_EQUAL, [](MBoxObject* left, MBoxObject* right){return left->handleGreaterEq(right);}},
                                                                {PLUS,          [](MBoxObject* left, MBoxObject* right){return left->handlePlus(right);}},
                                                                {MINUS,         [](MBoxObject* left, MBoxObject* right){return left->handleMinus(right);}},
                                                                {STAR,          [](MBoxObject* left, MBoxObject* right){return left->handleStar(right);}},
                                                                {SLASH,         [](MBoxObject* left, MBoxObject* right){return left->handleSlash(right);}},
                                                                {AND,           [](MBoxObject* left, MBoxObject* right){return left->handleAnd(right);}},
                                                                {OR,            [](MBoxObject* left, MBoxObject* right){return left->handleOr(right);}}};

void MBoxInterpreter::printFormatedInterpretation(Expr& e){
    MBoxObject* res = this->interpret(e);
    cout << res << endl; //print()? solucinar!!
}

MBoxObject* MBoxInterpreter::interpret(Expr& e){
    return e.accept(*this);
};

MBoxObject* MBoxInterpreter::interpretGrouping(Grouping& e){
    return this->interpret(*e.expression);
};

MBoxObject* MBoxInterpreter::interpretBinary(Binary& e){
    MBoxObject* left_value = this->interpret(*e.left);
    MBoxObject* right_value = this->interpret(*e.right);
    tokenType op_tt = (*e.op).token_type;
    MBoxObject* res = binaryClossures[op_tt](left_value, right_value);
    this->objects.push_back(res);
    return res;
};

MBoxObject* MBoxInterpreter::interpretLiteral(Literal& e){
    tokenType tt  = (*e.value).token_type;
    string lexeme = (*e.value).lexeme;
    MBoxObject* res = literalClosures[tt](lexeme);
    this->objects.push_back(res);
    return res;
};

MBoxObject* MBoxInterpreter::interpretUnary(Unary& e){
    tokenType op_tt  = (*e.op).token_type;
    MBoxObject* right_value = (*this).interpret(*e.right);
    MBoxObject* res = unaryCLosures[op_tt](right_value);
    this->objects.push_back(res);
    return res;
};

// STATEMENTS

void MBoxInterpreter::interpretProgram(vector<Stmt*> vs){
    for(Stmt* s: vs){
        this->interpretStmt(*s);
    } // ver MBox::run y ver si anda esto. makefile!
}

void MBoxInterpreter::interpretStmt(Stmt& s){
    return s.accept(*this);
}

void MBoxInterpreter::interpretExprStmt(ExprStmt& es){
    this->interpret(*es.expr);
    return;
}

void MBoxInterpreter::interpretPrintStmt(PrintStmt& ps){
    this->printFormatedInterpretation(*ps.print_expr);
}