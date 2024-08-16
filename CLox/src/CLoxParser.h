#ifndef CLOX_PARSER_H
#define CLOX_PARSER_H

#include "./AST.h"
#include "./token.h"
#include "./enums_and_maps.h"

class CLoxParser{
    public:
        CLoxParser(vector<Token> t);
        ~CLoxParser();
        Expr* parse();
    private:
        
        Expr* expression();
        Expr* equality();
        Expr* comparison();
        Expr* term();
        Expr* factor();
        Expr* unary();
        Expr* primary();
        
        bool match(tokenType t);
        bool match(vector<tokenType> vt);
        Expr* BinaryPositiveClossure(CLoxParser* parser, Expr* (CLoxParser::*expr_func)(), vector<tokenType> token_types);
        Token* consumeToken();

        vector<Token> tokens;
        vector<Expr*> expr_pointers;
        vector<Token*> token_pointers;
        unsigned int current;
        
};      

#endif