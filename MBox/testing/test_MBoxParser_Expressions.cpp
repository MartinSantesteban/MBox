#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../src/MBoxParser.h"
#include "../src/visitor.h"
#include "../src/AST.h"

bool test_literal(Token& t){
    vector<Token> tokens;
    tokens.push_back(t);
    MBoxParser p1(tokens);
    Literal l(&t);
    Expr* res = p1.parseExpression();
    return (l == *res);
}

bool test_parsing(vector<Token>& vt,Expr& e){
    Printer p;
    MBoxParser p1(vt);
    Expr* res = p1.parseExpression();
    //cout << p.visit(*res) << endl;
    return (e == *res);
}

bool test_binary_parsing(Token& op){
    vector<Token> tokens;
    Token t1(NUMBER, "33", 0);
    Token t2(NUMBER, "11", 0);
    tokens.push_back(t1);
    tokens.push_back(op);
    tokens.push_back(t2);

    Literal l1(&t1);
    Literal l2(&t2);
    Binary b(&l1, &op, &l2);

    return test_parsing(tokens, b);
}

bool test_binary_positive_parsing(Token& op1, Token& op2){
    vector<Token> tokens;
    Token t1(NUMBER, "50", 0);
    Token t3(NUMBER, "2", 0);
    Token t5(NUMBER, "5", 0);

    tokens.push_back(t1);
    tokens.push_back(op1);
    tokens.push_back(t3);
    tokens.push_back(op2);
    tokens.push_back(t5);

    Literal l1(&t1);
    Literal l2(&t3);
    Binary b1(&l1, &op1, &l2);

    Literal l3(&t5);
    Binary b2(&b1, &op2, &l3);

    return test_parsing(tokens, b2);
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
    Token op(SLASH, "/", 0);
    CHECK(test_binary_parsing(op));
}

TEST_CASE("Correct parsing of factor expression. -- STAR"){
    Token op(STAR, "*", 0);
    CHECK(test_binary_parsing(op));
}

TEST_CASE("Correct parsing of factor expression. -- (STAR | SLASH)*"){
    Token op1(STAR, "*", 0);
    Token op2(SLASH, "/", 0);
    CHECK(test_binary_positive_parsing(op1, op2));
}

TEST_CASE("Correct parsing of term expression. -- PLUS"){
    Token op(PLUS, "+", 0);
    CHECK(test_binary_parsing(op));
}


TEST_CASE("Correct parsing of term expression. -- MINUS"){
    Token op(MINUS, "-", 0);
    CHECK(test_binary_parsing(op));
}

TEST_CASE("Correct parsing of factor expression. -- (MINUS | PLUS)*"){
    Token op1(MINUS, "-", 0);
    Token op2(PLUS, "+", 0);
    CHECK(test_binary_positive_parsing(op1, op2));
}

TEST_CASE("Correct parsing of comparison expression. -- LESS"){
    Token op(LESS, "<", 0);
    CHECK(test_binary_parsing(op));
}

TEST_CASE("Correct parsing of comparison expression. -- LESS_EQUAL"){
    Token op(LESS_EQUAL, "<=", 0);
    CHECK(test_binary_parsing(op));
}

TEST_CASE("Correct parsing of comparison expression. -- GREATER"){
    Token op(GREATER, ">", 0);
    CHECK(test_binary_parsing(op));
}

TEST_CASE("Correct parsing of comparison expression. -- GREATER_EQUAL"){
    Token op(GREATER_EQUAL, ">=", 0);
    CHECK(test_binary_parsing(op));
}

TEST_CASE("Correct parsing of comparison expression. -- EQUAL_EQUAL"){
    Token op(EQUAL_EQUAL, "==", 0);
    CHECK(test_binary_parsing(op));
}

TEST_CASE("Correct parsing of comparison expression. -- BANG_EQUAL"){
    Token op(BANG_EQUAL, "!=", 0);
    CHECK(test_binary_parsing(op));
}

TEST_CASE("Correct parsing of factor expression. -- (EQUAL_EQUAL | BANG_EQUAL)*"){
    Token op1(EQUAL_EQUAL, "==", 0);
    Token op2(BANG_EQUAL, "!=", 0);
    CHECK(test_binary_positive_parsing(op1, op2));
}

TEST_CASE("Correct parsing of binary expression. -- AND"){
    Token op(AND, "and", 0);
    CHECK(test_binary_parsing(op));
}

TEST_CASE("Correct parsing of binary expression. -- OR"){
    Token op(OR, "or", 0);
    CHECK(test_binary_parsing(op));
}

TEST_CASE("Correct parsing of literal grouping expression. -- (expr)"){
    vector<Token> tokens;
    Token t1(L_PAREN, "(", 0);
    Token t2(NUMBER, "7", 0);
    Token t3(R_PAREN, ")", 0);

    tokens.push_back(t1);
    tokens.push_back(t2);
    tokens.push_back(t3);

    Literal l(&t2);
    Grouping g(&l);

    CHECK(test_parsing(tokens, g));
}

TEST_CASE("Correct parsing of literal grouping expression. -- catch missing R_PAREN"){
    vector<Token> tokens;
    Token t1(L_PAREN, "(", 0);
    Token t2(NUMBER, "7", 0);

    tokens.push_back(t1);
    tokens.push_back(t2);

    Literal l(&t2);
    Grouping g(&l);
    CHECK_THROWS_WITH(test_parsing(tokens, g), "MBoxParser :: line 0 -- Right parenthesis expected.");
}

TEST_CASE("Correct parsing of literal grouping expression. -- catch missing L_PAREN"){
    vector<Token> tokens;
    Token t1(NUMBER, "7", 0);
    Token t2(R_PAREN, ")", 0);

    tokens.push_back(t1);
    tokens.push_back(t2);

    Literal l(&t2);
    Grouping g(&l);
    CHECK_THROWS_WITH(test_parsing(tokens, g), "MBoxParser :: line 0 -- Left parenthesis expected.");
}

TEST_CASE("Correct parsing of literal grouping expression. -- catch missing L_PAREN"){
    vector<Token> tokens;
    Token t1(R_PAREN, ")", 0);

    tokens.push_back(t1);

    Literal l(&t1);
    CHECK_THROWS_WITH(test_parsing(tokens, l), "MBoxParser :: line 0 -- Left parenthesis expected.");
}

TEST_CASE("Correct parsing of literal grouping expression. -- catch single invalid token"){
    vector<Token> tokens;
    Token t1(PLUS, "+", 0);

    tokens.push_back(t1);

    Literal l(&t1);
    CHECK_THROWS_WITH(test_parsing(tokens, l), "MBoxParser :: line 0 -- Invalid token encountered.");
}

TEST_CASE("Correct parsing of literal grouping expression. -- catch invalid tokens"){
    vector<Token> tokens;
    Token t1(PLUS, "+", 0);
    Token t2(NUMBER, "7", 0);

    tokens.push_back(t1);
    tokens.push_back(t2);

    Literal l(&t1);
    CHECK_THROWS_WITH(test_parsing(tokens, l), "MBoxParser :: line 0 -- Invalid token encountered.");
}

TEST_CASE("Correct parsing of literal grouping expression. -- catch dangling token after correct expression"){
    vector<Token> tokens;
    Token t1(NUMBER, "7", 0);
    Token t2(PLUS, "+", 0);
    Token t3(NUMBER, "7", 0);
    Token t4(SLASH, "/", 0);

    tokens.push_back(t1);
    tokens.push_back(t2);
    tokens.push_back(t3);
    tokens.push_back(t4);

    Literal l(&t1);
    CHECK_THROWS_WITH(test_parsing(tokens, l), "MBoxParser :: line 0 -- Invalid token encountered.");
}

