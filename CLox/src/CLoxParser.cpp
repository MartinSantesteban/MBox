#include "./CLoxParser.h"
#include "./visitor.h"

CLoxParser::CLoxParser(vector<Token> t){
    this->tokens = t;
    this->current = 0;
    this->expr_pointers = vector<Expr*>();
    this->token_pointers = vector<Token*>();
}

bool CLoxParser::match(tokenType tt){
    return (current < tokens.size() && tokens[current].token_type == tt);
}

bool CLoxParser::match(vector<tokenType> tts){
    for(auto& tt : tts){
        if(tokens[current].token_type == tt){
            return current < tokens.size();
        }
    }
    return false;
}

Token* CLoxParser::consumeToken(){
    Token* token_ptr = new Token(this->tokens[current]);
    this->token_pointers.push_back(token_ptr);
    current++;
    return token_ptr;
}

Expr* CLoxParser::BinaryPositiveClossure(CLoxParser* parser, Expr* (CLoxParser::*expr_func)(), vector<tokenType> token_types){
    Expr* right = (parser->*expr_func)();
    while(match(token_types)){
        Token* binary_token_operator = consumeToken();
        Expr* left = (parser->*expr_func)();
        right = new Binary(right, binary_token_operator, left);  
        this->expr_pointers.push_back(right);
    }
    return right;
}

Expr* CLoxParser::parse(){
    Expr* res = expression();
    if(match(R_PAREN)) throw invalid_argument("CLoxParser :: line " + to_string(this->tokens[current].line) + " -- Left parenthesis expected.");
    return res;
}

Expr* CLoxParser::expression(){
    Expr* res = equality();
    return res;
}
Expr* CLoxParser::equality(){
    vector<tokenType> equality_operators = {EQUAL_EQUAL, BANG_EQUAL};
    return BinaryPositiveClossure(this, &CLoxParser::comparison, equality_operators);
}

Expr* CLoxParser::comparison(){
    vector<tokenType> comparison_operators = {LESS, LESS_EQUAL, GREATER, GREATER_EQUAL};
    return BinaryPositiveClossure(this, &CLoxParser::term, comparison_operators);
}

Expr* CLoxParser::term(){
    vector<tokenType> term_operators = {PLUS, MINUS, OR};
    return BinaryPositiveClossure(this, &CLoxParser::factor, term_operators);
}

Expr* CLoxParser::factor(){
    vector<tokenType> factor_operators = {STAR, SLASH, AND};
    return BinaryPositiveClossure(this, &CLoxParser::unary, factor_operators);
}

Expr* CLoxParser::unary(){
    if(match(BANG) || match(MINUS)){
        Token* bang_token_ptr = consumeToken();
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
        Token* token_ptr = consumeToken();
        Expr* res = new Literal(token_ptr);
        this->expr_pointers.push_back(res);
        return res;
    }
    if(match(L_PAREN)){
        current++;
        Expr* res = expression();
        res = new Grouping(res);
        this->expr_pointers.push_back(res);
        if(!match(R_PAREN)) throw invalid_argument("CLoxParser :: line " + to_string(this->tokens[current - 1].line) + " -- Right parenthesis expected.");        
        current++;
        return res;
    }
    if(match(R_PAREN)) throw invalid_argument("CLoxParser :: line " + to_string(this->tokens[current].line) + " -- Left parenthesis expected."); 
    throw invalid_argument("CLoxParser :: line " + to_string(this->tokens[current].line) + " -- Invalid token encountered.");
}

CLoxParser::~CLoxParser(){
    for(auto &ptr : this->expr_pointers){
        delete ptr;
    }
    for(auto &ptr : this->token_pointers){
        delete ptr;
    }
}