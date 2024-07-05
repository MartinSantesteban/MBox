#include "AST.cpp"

// Each grammar rule becomes a method 
// El parser agarra los tokens y hace el AST! 
// Como las expresiones tienen estructura de arbol, vas devolviendo expresiones
// a medida que avanzas.

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
        */
        Expr primary();


        bool matchTokenTypes(vector<tokenType> tts);
        void advance();
};