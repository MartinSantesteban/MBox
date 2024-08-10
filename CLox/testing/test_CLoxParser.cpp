#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/CLoxParser.h"
#include "../src/visitor.h"
#include "../src/AST.h"

bool test_literal(Token& t){
    vector<Token> tokens;
    tokens.push_back(t);
    CLoxParser p1(tokens);
    Literal l(&t);
    Expr* res = p1.parse();
    return (l == *res);
}

bool test_parsing(vector<Token>& vt,Expr& e){
    Printer p;
    CLoxParser p1(vt);
    Expr* res = p1.parse();
    cout << p.visit(*res) << endl;
    return (e == *res);
}


TEST_CASE("Correct parsing of literal expression. -- NUMBER"){
    Token t(NUMBER, "7", 0);
    CHECK(test_literal(t));
}

TEST_CASE("Correct parsing of literal expression. -- STRING"){
    Token t(STRING, "   LLALALA", 0);
    CHECK(test_literal(t));
}

TEST_CASE("Correct parsing of literal expression. -- TRUE"){
    Token t(TRUE, "TRUE", 0);
    CHECK(test_literal(t));
}

TEST_CASE("Correct parsing of literal expression. -- FALSE"){
    Token t(FALSE, "FALSE", 0);
    CHECK(test_literal(t));
}

TEST_CASE("Correct parsing of literal expression. -- NIL"){
    Token t(NIL, "NIL", 0);
    CHECK(test_literal(t));
}

TEST_CASE("Correct parsing of unary expression. -- NOT"){
    vector<Token> tokens;
    Token t1(BANG, "!", 0);
    Token t2(TRUE, "TRUE", 0);
    tokens.push_back(t1);
    tokens.push_back(t2);

    Literal l(&t2);
    Unary u(&t1, &l);

    CHECK(test_parsing(tokens, u));
}

TEST_CASE("Correct parsing of unary expression. -- MINUS"){
    vector<Token> tokens;
    Token t1(MINUS, "-", 0);
    Token t2(NUMBER, "89", 0);
    tokens.push_back(t1);
    tokens.push_back(t2);

    Literal l(&t2);
    Unary u(&t1, &l);

    CHECK(test_parsing(tokens, u));
}

TEST_CASE("Correct parsing of factor expression. -- SLASH"){
    vector<Token> tokens;
    Token t1(NUMBER, "33", 0);
    Token t2(SLASH, "/", 0);
    Token t3(NUMBER, "11", 0);
    tokens.push_back(t1);
    tokens.push_back(t2);
    tokens.push_back(t3);

    Literal l1(&t1);
    Literal l2(&t3);
    Binary b(&l1, &t2, &l2);
    CHECK(test_parsing(tokens, b));
}

TEST_CASE("Correct parsing of factor expression. -- SLASH*"){
    vector<Token> tokens;
    Token t1(NUMBER, "50", 0);
    Token t2(SLASH, "/", 0);
    Token t3(NUMBER, "2", 0);
    Token t4(SLASH, "/", 0);
    Token t5(NUMBER, "5", 0);

    tokens.push_back(t1);
    tokens.push_back(t2);
    tokens.push_back(t3);
    tokens.push_back(t4);
    tokens.push_back(t5);

    Literal l1(&t1);
    Literal l2(&t3);
    Binary b1(&l1, &t2, &l2);

    Literal l3(&t5);
    Binary b2(&b1, &t4, &l3);

    CHECK(test_parsing(tokens, b2));
}
