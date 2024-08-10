#include "./AST.h"
#include "./token.h"
#include "./enums_and_maps.h"
#include <stdexcept>


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

        vector<Token> tokens;
        vector<Expr*> expr_pointers;
        vector<Token*> token_pointers;
        unsigned int current;
        
};      