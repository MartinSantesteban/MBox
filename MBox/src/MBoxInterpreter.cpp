#include "./MBoxInterpreter.h"

map<tokenType, function<MBoxObject*(string, MBoxEnvironment*)>>  literalClosures = {{STRING,    [](string lexeme, MBoxEnvironment* e){return new MBoxString(lexeme);}},
                                                                 {NUMBER,     [](string lexeme, MBoxEnvironment* e){return new MBoxNumber((double) stoi(lexeme));}},
                                                                 {TRUE,       [](string lexeme, MBoxEnvironment* e){return new MBoxBoolean(true);}},
                                                                 {FALSE,      [](string lexeme, MBoxEnvironment* e){return new MBoxBoolean(false);}},
                                                                 {NIL,        [](string lexeme, MBoxEnvironment* e){return new MBoxNil();}},
                                                                 {IDENTIFIER, [](string lexeme, MBoxEnvironment* e){return e->getVariableValue(lexeme);}}};

map<tokenType,function<MBoxObject*(MBoxObject* right)>> unaryCLosures = {{BANG,   [](MBoxObject* right){return (*right).handleBang();}},
                                                                         {MINUS,  [](MBoxObject* right){return (*right).handleMinus();}}};

map<tokenType, function<MBoxObject*(MBoxObject* left, MBoxObject* right)>>  binaryClossures = {
                                                                {EQUAL_EQUAL,   [](MBoxObject* left, MBoxObject* right){return left->handleEq(right);}},
                                                                {BANG_EQUAL,    [](MBoxObject* left, MBoxObject* right){return left->handleNeq(right);}},
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
    MBoxObject* res = this->interpretExpr(e);
    res->print();
}

MBoxObject* MBoxInterpreter::interpretExpr(Expr& e){
    return e.accept(*this);
};

MBoxObject* MBoxInterpreter::interpretGrouping(Grouping& e){
    return this->interpretExpr(*e.expression);
};

MBoxObject* MBoxInterpreter::interpretBinary(Binary& e){
    MBoxObject* left_value = this->interpretExpr(*e.left);
    MBoxObject* right_value = this->interpretExpr(*e.right);
    tokenType op_tt = (*e.op).token_type;
    int line = (*e.op).line;
    try{
        MBoxObject* res = binaryClossures[op_tt](left_value, right_value);
        this->objects.insert(res);
        return res;
    }catch(const std::invalid_argument& exc){
        throw invalid_argument("[MBoxInterpreter] in line " + to_string(line) + ": " + (string) exc.what());
    }
};

MBoxObject* MBoxInterpreter::interpretLiteral(Literal& e){
    tokenType tt  = (*e.value).token_type;
    string lexeme = (*e.value).lexeme;
    int line = (*e.value).line;
    try{
        MBoxObject* res = literalClosures[tt](lexeme, &(this->environment));
        this->objects.insert(res);
        return res;
    }catch(const std::invalid_argument& exc){
        throw invalid_argument("[MBoxInterpreter] in line " + to_string(line) + ": " + (string) exc.what());
    }
    
};

MBoxObject* MBoxInterpreter::interpretUnary(Unary& e){
    tokenType op_tt  = (*e.op).token_type;
    MBoxObject* right_value = (*this).interpretExpr(*e.right);
    int line = (*e.op).line;
    try{
        MBoxObject* res = unaryCLosures[op_tt](right_value);
        this->objects.insert(res);
        return res;
    }catch(const std::invalid_argument& exc){
        throw invalid_argument("[MBoxInterpreter] in line " + to_string(line) + ": " + (string) exc.what());
    }
};

// STATEMENTS

void MBoxInterpreter::interpretProgram(vector<Stmt*> vs){
    for(Stmt* s: vs){
        this->interpretStmt(*s);
    } 
}

void MBoxInterpreter::interpretStmt(Stmt& s){
    return s.accept(*this);
}

void MBoxInterpreter::interpretExprStmt(ExprStmt& es){
    this->interpretExpr(*es.expr);
    return;
}

void MBoxInterpreter::interpretPrintStmt(PrintStmt& ps){
    this->printFormatedInterpretation(*ps.print_expr);
}

void MBoxInterpreter::interpretItemDeclStmt(ItemDeclStmt& ids){
    this->environment.setVariableValue(ids.itemName(), this->interpretExpr(*ids.value_expr)); 
}

void MBoxInterpreter::interpretRedefinitionStmt(RedefinitionStmt& rs){
    this->environment.redefineVariableValue(rs.itemName(), this->interpretExpr(*rs.value_expr)); 
}

MBoxInterpreter::~MBoxInterpreter(){
    for(auto &ptr : this->objects){     
        delete ptr;
    }
}

MBoxObject* MBoxInterpreter::getVariableValue(string varName){
    return this->environment.getVariableValue(varName);
}