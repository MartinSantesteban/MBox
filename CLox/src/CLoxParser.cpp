#include "./CLoxParser.h"
#include "./visitor.h"

Printer p;

CLoxParser::CLoxParser(vector<Token> t){
    this->tokens = t;
    this->current = 0;
}

bool CLoxParser::match(tokenType tt){
    return (current < tokens.size() && tokens[current].token_type == tt);
}

Expr* CLoxParser::parse(){
    Expr* res = expression();
    return res;
}

Expr* CLoxParser::expression(){
    Expr* res = equality();
    return res;
}

Expr* CLoxParser::equality(){
    Expr* res = comparison();
    return res;
}

Expr* CLoxParser::comparison(){
    Expr* res = term();
    return res;
}

Expr* CLoxParser::term(){
    Expr* res = factor();
    return res;
}

Expr* CLoxParser::factor(){
    Expr* res = unary();
    return res;
}

Expr* CLoxParser::unary(){
    Expr* res = primary();
    return res;
}

Expr* CLoxParser::primary(){
    if(match(NUMBER)){
        Token literal_token = this->tokens[current];
        current++;
        Expr* res = new Literal(&literal_token);
        this->pointers.push_back(res);
        return res;
    }
    throw invalid_argument("NO PARSEA!");
}


CLoxParser::~CLoxParser(){
    cout << this->pointers.size() << endl;
    for(auto &ptr : this->pointers){
        delete ptr;
    }
}

