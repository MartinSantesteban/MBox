#include "./CLoxParser.h"
#include "./visitor.h"

Printer p;

CLoxParser::CLoxParser(vector<Token> t){
    this->tokens = t;
    this->current = 0;
    this->expr_pointers = vector<Expr*>();
    this->token_pointers = vector<Token*>();
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
    Expr* right = unary();
    while(match(SLASH)){
        Token* factor_token_ptr = new Token(this->tokens[current]);
        this->token_pointers.push_back(factor_token_ptr);
        current++;
        Expr* left = unary();
        right = new Binary(right, factor_token_ptr, left);  // <- asociativo a izquierda!
        this->expr_pointers.push_back(right);
    }
    return right;
}

Expr* CLoxParser::unary(){
    if(match(BANG) || match(MINUS)){
        Token* bang_token_ptr = new Token(this->tokens[current]);
        this->token_pointers.push_back(bang_token_ptr);
        current++;
        Expr* right = primary();
        Expr* res = new Unary(bang_token_ptr, right);
        this->expr_pointers.push_back(res);
        return res;
    }else{
        Expr* res = primary();
        return res;
    }
}

Expr* CLoxParser::primary(){
    if(match(NUMBER) || match(STRING) || match(TRUE) || match(FALSE) || match(NIL)){
        Token* token_ptr = new Token(this->tokens[current]);
        this->token_pointers.push_back(token_ptr);
        current++;
        Expr* res = new Literal(token_ptr);
        this->expr_pointers.push_back(res);
        return res;
    }
    throw invalid_argument("NO PARSEA!");
}


CLoxParser::~CLoxParser(){
    for(auto &ptr : this->expr_pointers){
        delete ptr;
    }
    for(auto &ptr : this->token_pointers){
        delete ptr;
    }
}

