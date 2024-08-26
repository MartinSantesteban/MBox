// Aca tengo el Parser pre refactor, en caso de necesitar debugear y que entorpezca el refactor o haya que agregar features a no terminales en especial. 


#include "./visitor.h"

Printer p;

MBoxParser::MBoxParser(vector<Token> t){
    this->tokens = t;
    this->current = 0;
    this->expr_pointers = vector<Expr*>();
    this->token_pointers = vector<Token*>();
}

bool MBoxParser::match(tokenType tt){
    return (current < tokens.size() && tokens[current].token_type == tt);
}

Expr* MBoxParser::parse(){
    Expr* res = expression();
    if(match(R_PAREN)) throw invalid_argument("MBoxParser -- Left parenthesis expected.");
    return res;
}

Expr* MBoxParser::expression(){
    Expr* res = equality();
    return res;
}

Expr* MBoxParser::equality(){
    Expr* right = comparison();
    while(match(EQUAL_EQUAL) || match(BANG_EQUAL)){
        Token* cmp_token_ptr = new Token(this->tokens[current]);
        this->token_pointers.push_back(cmp_token_ptr);
        current++;
        Expr* left = term();
        right = new Binary(right, cmp_token_ptr, left);  
        this->expr_pointers.push_back(right);
    }
    return right;
}

Expr* MBoxParser::comparison(){
    Expr* right = term();
    while(match(LESS) || match(LESS_EQUAL) || match(GREATER) || match(GREATER_EQUAL)){
        Token* cmp_token_ptr = new Token(this->tokens[current]);
        this->token_pointers.push_back(cmp_token_ptr);
        current++;
        Expr* left = term();
        right = new Binary(right, cmp_token_ptr, left);  
        this->expr_pointers.push_back(right);
    }
    return right;
}

Expr* MBoxParser::term(){
    Expr* right = factor();
    while(match(PLUS) || match(MINUS)){
        Token* term_token_ptr = new Token(this->tokens[current]);
        this->token_pointers.push_back(term_token_ptr);
        current++;
        Expr* left = factor();
        right = new Binary(right, term_token_ptr, left);  
        this->expr_pointers.push_back(right);
    }
    return right;
}

Expr* MBoxParser::factor(){
    Expr* right = unary();
    while(match(SLASH) || match(STAR)){
        Token* factor_token_ptr = new Token(this->tokens[current]);
        this->token_pointers.push_back(factor_token_ptr);
        current++;
        Expr* left = unary();
        right = new Binary(right, factor_token_ptr, left);  // <- asociativo a izquierda!
        this->expr_pointers.push_back(right);
    }
    return right;
}

Expr* MBoxParser::unary(){
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

Expr* MBoxParser::primary(){
    if(match(NUMBER) || match(STRING) || match(TRUE) || match(FALSE) || match(NIL)){
        Token* token_ptr = new Token(this->tokens[current]);
        this->token_pointers.push_back(token_ptr);
        current++;
        Expr* res = new Literal(token_ptr);
        this->expr_pointers.push_back(res);
        return res;
    }
    if(match(L_PAREN)){
        current++;
        Expr* res = expression();
        res = new Grouping(res);
        this->expr_pointers.push_back(res);
        if(match(R_PAREN)){
            current++;
        }else{
            throw invalid_argument("MBoxParser -- Right parenthesis expected.");        
        }
        return res;
    }
    if(match(R_PAREN)) throw invalid_argument("MBoxParser -- Left parenthesis expected."); // este esta solo para que si te encontras un R_PAREN solo sea mas informativo el mensaje
    throw invalid_argument("MBoxParser -- Invalid token type encountered.");
}


MBoxParser::~MBoxParser(){
    for(auto &ptr : this->expr_pointers){
        delete ptr;
    }
    for(auto &ptr : this->token_pointers){
        delete ptr;
    }
}