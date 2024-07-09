#include "CLoxParser.h"

Parser::Parser(vector<Token> t){
    this->tokens = t;
    this->current = 0;
}

bool Parser::match(tokenType tt){
    return (tokens[current].token_type == tt);
}

Expr Parser::parse(){
    return expression();
}

Expr Parser::expression(){
    return equality();
}

Expr Parser::equality(){
    Expr res = comparison();
    while(match(EQUAL_EQUAL) || match(BANG_EQUAL)){
        Token eq_operator = tokens[current];
        current++;
        Expr right = comparison();
        Expr res = Binary(&res, &eq_operator, &right);
    }
    return res;
}

Expr Parser::comparison(){
    Expr res = term();
    while(match(LESS) || match(LESS_EQUAL) || match(GREATER) || match(GREATER_EQUAL)){
        Token comparison_operator = tokens[current];
        current++;
        Expr right = term();
        Expr res = Binary(&res, &comparison_operator, &right);
    }
    return res;
}

Expr Parser::term(){
    Expr res = factor();
    while(match(SLASH) || match(PLUS)){
        Token term_operator = tokens[current];
        current++;
        Expr right = factor();
        Expr res = Binary(&res, &term_operator, &right);
    }
    return res;
}

Expr Parser::factor(){
    Expr res = unary();
    while(match(SLASH) || match(PLUS)){
        Token comparison_operator = tokens[current];
        current++;
        Expr right = unary();
        Expr res = Binary(&res, &comparison_operator, &right);
    }
    return res;
}

Expr Parser::unary(){
    if(match(BANG) || match(SLASH)){
        Token unary_operator = tokens[current];
        current++;
        Expr right = primary();
        Expr res = Unary(&unary_operator, &right);
        return res;
    }else{
        return primary();
    }
    
}

Expr Parser::primary(){
    if(match(NUMBER) || match(STRING) || match(TRUE) || match(FALSE) || match(NIL)){
        Token literal_token = tokens[current];
        current++;
        Expr res = Literal(&literal_token);
        return res;
    }else{
        if(match(L_PAREN) && tokens[tokens.size() - 1].token_type == R_PAREN){
            current++;
            Expr e = expression();
            Expr res = Grouping(&e);
            return res;
        }
    }
    throw invalid_argument("NO PARSEA!");
}