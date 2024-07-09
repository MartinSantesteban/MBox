#include "./AST.h"
#include "./token.h"
#include "./enums_and_maps.h"
#include <stdexcept>


class Parser{
    public:
        vector<Token> tokens;
        int current;
        Parser(vector<Token> t);
        Expr parse();
    private:
        
        Expr expression();
        Expr equality();
        Expr comparison();
        Expr term();
        Expr factor();
        Expr unary();
        Expr primary();
        
        bool match(tokenType t);
};