#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/CLoxParser.h"
#include "../src/visitor.h"

TEST_CASE("Correct parsing of literal expression. -- NUMBER"){
    Printer p;
    vector<Token> tokens;
    Token t(NUMBER, "7", 0);
    tokens.push_back(t);
    Parser p1(tokens);
    CHECK(p1.parse() == Literal(&t));
    Expr res = p1.parse();
    CHECK(p.visit(res) == "7");
}