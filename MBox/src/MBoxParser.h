#ifndef MBox_PARSER_H
#define MBox_PARSER_H

#include "./enums_and_maps.h"
#include "./token.h"
#include "./AST.h"
#include "./SST.h"


class MBoxParser{
    public:
        MBoxParser(vector<Token> t);
        ~MBoxParser();
        Expr* parseExpression();
        Stmt* parseStmt();
        vector<Stmt*> parseProgram();
    private:
        
        Expr* expression();
        Expr* equality();
        Expr* comparison();
        Expr* term();
        Expr* factor();
        Expr* unary();
        Expr* primary();

        Stmt* declaration();
        Stmt* itemDeclStmt();
        Stmt* statement();
        Stmt* printStmt();
        Stmt* redefinitionStmt();
        Stmt* exprStmt();
        
        bool match(tokenType t);
        bool match(vector<tokenType> vt);
        Expr* BinaryPositiveClossure(MBoxParser* parser, Expr* (MBoxParser::*expr_func)(), vector<tokenType> token_types);
        Token* consumeToken();

        vector<Token> tokens;
        vector<Expr*> expr_pointers;
        vector<Token*> token_pointers;
        vector<Stmt*> stmt_pointers;
        unsigned int current;
        
};      

#endif