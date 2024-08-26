#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../src/SST.h"
#include "../src/AST.h"
#include "../src/token.h"
#include "../src/MBoxParser.h"

TEST_CASE("Correct parsing of Print Statement."){
    vector<Token> tokens;
    Token t1(PRINT, "print", 0);
    Token t2(NUMBER, "7", 0);
    Token t3(SEMICOLON, ";", 0);

    tokens.push_back(t1);
    tokens.push_back(t2);
    tokens.push_back(t3);

    MBoxParser p(tokens);

    Literal l(&t2);    
    PrintStmt ps(&l);

    Stmt* res = p.parseStmt();
    CHECK(*res == ps);
}

TEST_CASE("Correct parsing of Print Statement. -- Missing semicolon throws an error."){
    vector<Token> tokens;
    Token t1(PRINT, "print", 0);
    Token t2(NUMBER, "7", 0);

    tokens.push_back(t1);
    tokens.push_back(t2);

    MBoxParser p(tokens);

    Literal l(&t2);    
    PrintStmt ps(&l);

    CHECK_THROWS_WITH(p.parseStmt(), "MBoxParser :: line 0 -- Semicolon expected.");
}

TEST_CASE("Correct parsing of Expr Statement."){
    vector<Token> tokens;
    Token t1(NUMBER, "7", 0);
    Token t2(SEMICOLON, ";", 0);

    tokens.push_back(t1);
    tokens.push_back(t2);

    MBoxParser p(tokens);

    Literal l(&t1);    
    ExprStmt ps(&l);

    Stmt* res = p.parseStmt();
    CHECK(*res == ps);
}

TEST_CASE("Correct parsing of Expr Statement. -- Missing semicolon throws an error."){
    vector<Token> tokens;
    Token t1(NUMBER, "7", 0);

    tokens.push_back(t1);

    MBoxParser p(tokens);

    Literal l(&t1);    
    ExprStmt ps(&l);

    CHECK_THROWS_WITH(p.parseStmt(), "MBoxParser :: line 0 -- Semicolon expected.");
}

TEST_CASE("Correct parsing of program."){
    Token t1(PRINT, "print", 0);
    Token t2(NUMBER, "7", 0);
    Token t3(SEMICOLON, ";", 0);
    Token t4(NUMBER, "8", 0);
    Token t5(SEMICOLON, ";", 0);
    Token t6(PRINT, "print", 0);
    Token t7(NUMBER, "9", 0);
    Token t8(SEMICOLON, ";", 0);

    vector<Token> tokens = {t1, t2, t3, t4, t5, t6, t7, t8};

    MBoxParser p(tokens);

    Literal l1(&t2);    
    Literal l2(&t4);    
    Literal l3(&t7); 

    PrintStmt ps1(&l1);
    ExprStmt es(&l2);
    PrintStmt ps2(&l3);

    auto res = p.parseProgram();
    CHECK(*res[0] == ps1);
    CHECK(*res[1] == es);
    CHECK(*res[2] == ps2);
}