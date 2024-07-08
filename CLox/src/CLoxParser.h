#include "AST.cpp"

class Parser{
    public:
        vector<Token> tokens;
        int current;
        Parser(vector<Token> t){
            this->tokens = t;
            this->current = 0;
        }

    private:
        /*
        Expr expression();
        Expr equality();
        Expr comparison();
        Expr term();
        Expr factor();
        Expr unary();
        Expr primary();
        */
};