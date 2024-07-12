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
    return expression();
}

Expr* CLoxParser::expression(){
    return equality();
}

Expr* CLoxParser::equality(){
    Expr* res = comparison();
    while(match(EQUAL_EQUAL) || match(BANG_EQUAL)){
        Token eq_operator = tokens[current];
        current++;
        Expr* right = comparison();
        Expr* res = new Binary(res, &eq_operator, right);
        this->pointers.push_back(res);
    }
    return res;
}

Expr* CLoxParser::comparison(){
    Expr* res = term();
    while(match(LESS) || match(LESS_EQUAL) || match(GREATER) || match(GREATER_EQUAL)){
        Token comparison_operator = tokens[current];
        current++;
        Expr* right = term();
        Expr* res = new Binary(res, &comparison_operator, right);
        this->pointers.push_back(res);
    }
    return res;
}

Expr* CLoxParser::term(){
    Expr* res = factor();
    while(match(SLASH) || match(PLUS)){
        Token term_operator = tokens[current];
        current++;
        Expr* right = factor();
        Expr* res = new Binary(res, &term_operator, right);
        this->pointers.push_back(res);
    }
    return res;
}

Expr* CLoxParser::factor(){
    Expr* res = unary();
    while(match(SLASH) || match(PLUS)){
        Token comparison_operator = tokens[current];
        current++;
        Expr* right = unary();
        Expr* res = new Binary(res, &comparison_operator, right);
        this->pointers.push_back(res);
    }
    //cout << p.visit(*res) << endl;
    return res;
}

Expr* CLoxParser::unary(){
    if(match(BANG) || match(SLASH)){
        Token unary_operator = tokens[current];
        current++;
        Expr* right = primary();
        Expr* res = new Unary(&unary_operator, right);
        this->pointers.push_back(res);
        return res;
    }else{
        Expr* res = primary();
        return res;
    }
}

Expr* CLoxParser::primary(){
    if(match(NUMBER) || match(STRING) || match(TRUE) || match(FALSE) || match(NIL)){
        Token literal_token = tokens[current];
        current++;
        Expr* res = new Literal(&literal_token);
        this->pointers.push_back(res);
        return res;
    }else{
        if(match(L_PAREN) && tokens[tokens.size() - 1].token_type == R_PAREN){
            current++;
            Expr* e = expression();
            Expr* res = new Grouping(e);
            this->pointers.push_back(res);
            return res;
        }
    }
    throw invalid_argument("NO PARSEA!");
}

CLoxParser::~CLoxParser(){
    cout << this->pointers.size() << endl;
    for(auto &ptr : this->pointers){
        delete ptr;
    }
}
