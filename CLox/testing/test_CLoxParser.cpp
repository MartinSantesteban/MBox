#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/CLoxParser.h"
#include "../src/visitor.h"
#include "../src/AST.h"

TEST_CASE("Correct parsing of literal expression. -- NUMBER"){
    Printer p;
    vector<Token> tokens;
    Token t(NUMBER, "7", 0);
    tokens.push_back(t);
    CLoxParser p1(tokens);
    Literal l(&t);
    Expr* x = p1.parse();
    cout << "Visit Literal l: " << p.visit(l) << endl;
    cout << "Visit expr *x: " << p.visit(*x) << endl;
    CHECK(typeid(*x) == typeid(l));
    CHECK((*x) == l);
    
}