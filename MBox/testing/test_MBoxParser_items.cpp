#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../src/MBoxParser.h"
#include "../src/visitor.h"
#include "../src/AST.h"
#include "../src/SST.h"
#include "../src/token.h"

TEST_CASE("Correct parsing of item declaration statement."){
    // item num = 43;  -- LEXER --> [ITEM, "item", 0][IDENTIFIER, "num", 0][EQUAL, "=", 0][NUMBER, 43, 0][SEMICOLON, ";", 0]
    vector<Token> tokens;
    Token t1(ITEM, "item", 0);
    Token t2(IDENTIFIER, "num", 0);
    Token t3(EQUAL, "=", 0);
    Token t4(NUMBER, "43", 0);
    Token t5(SEMICOLON, ";", 0);

    tokens.push_back(t1);
    tokens.push_back(t2);
    tokens.push_back(t3);
    tokens.push_back(t4);
    tokens.push_back(t5);

    MBoxParser mp(tokens);
    Stmt* out = mp.parseStmt();

    Literal l(&t4);
    ItemDeclStmt it(&t2, &l);  

    CHECK(*out == it);

}

TEST_CASE("Correct parsing of item declaration statement with complex expression."){
    // item num = 43;  -- LEXER --> [ITEM, "item", 0][IDENTIFIER, "num", 0][EQUAL, "=", 0][NUMBER, 43, 0][SEMICOLON, ";", 0]
    vector<Token> tokens;
    Token t1(ITEM, "item", 0);
    Token t2(IDENTIFIER, "num", 0);
    Token t3(EQUAL, "=", 0);
    Token t4(NUMBER, "43", 0);
    Token t5(PLUS, "+", 0);
    Token t6(SEMICOLON, ";", 0);

    tokens.push_back(t1);
    tokens.push_back(t2);
    tokens.push_back(t3);
    tokens.push_back(t4);
    tokens.push_back(t5);
    tokens.push_back(t4);
    tokens.push_back(t5);
    tokens.push_back(t4);
    tokens.push_back(t6);

    MBoxParser mp(tokens);
    Stmt* out = mp.parseStmt();

    Literal l1(&t4);
    Literal l2(&t4);
    Binary b1(&l1, &t5, &l2);
    Literal l3(&t4);
    Binary b2(&b1, &t5, &l3);

    ItemDeclStmt it(&t2, &b2);  

    CHECK(*out == it);

}

TEST_CASE("Correct parsing of item declaration statement."){
    // item num = 43;  -- LEXER --> [ITEM, "item", 0][IDENTIFIER, "num", 0][EQUAL, "=", 0][NUMBER, 43, 0][SEMICOLON, ";", 0]
    vector<Token> tokens;
    
    Token t1(IDENTIFIER, "num", 0);
    Token t2(SEMICOLON, ";", 0);

    tokens.push_back(t1);
    tokens.push_back(t2);

    MBoxParser mp(tokens);
    Stmt* out = mp.parseStmt();

    Literal l(&t1);
    ExprStmt es(&l);

    CHECK(*out == es);

}