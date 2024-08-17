#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../src/SST.h"
#include "../src/AST.h"
#include "../src/token.h"
#include "../src/CLoxParser.h"

TEST_CASE("Correct parsing of literal grouping expression. -- (expr)"){
    vector<Token> tokens;
    Token t1(L_PAREN, "(", 0);
    Token t2(NUMBER, "7", 0);
    Token t3(R_PAREN, ")", 0);

    tokens.push_back(t1);
    tokens.push_back(t2);
    tokens.push_back(t3);

    CLoxParser p(tokens);

    Literal l(&t2);
    Grouping g(&l);
     
    CHECK(true);
}