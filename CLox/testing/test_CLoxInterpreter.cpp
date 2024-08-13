#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/CLoxInterpreter.h"
#include "../src/AST.h"
#include "../src/token.h"

TEST_CASE("Testing: Correct interpretation of Literal expression. -- STRING"){
    Token t(STRING, "ABC", 0);
	Literal l(&t);

    CLoxInterpreter i;
    string interpretation = any_cast<string>(i.interpret(l));
    CHECK(interpretation == "ABC");
}

TEST_CASE("Testing: Correct interpretation of Literal expression. -- NUMBER"){
    Token t(NUMBER, "95", 0);
	Literal l(&t);

    CLoxInterpreter i;
    double interpretation = any_cast<double>(i.interpret(l));
    CHECK(interpretation == 95);
}

TEST_CASE("Testing: Correct interpretation of Literal expression. -- BOOLS"){
    Token t(TRUE, "True", 0);
	Literal l(&t);

    CLoxInterpreter i;
    bool interpretation = any_cast<bool>(i.interpret(l));
    CHECK(interpretation);

    Token t2(FALSE, "False", 0);
	Literal l2(&t2);

    interpretation = any_cast<bool>(i.interpret(l2));
    CHECK(!interpretation);

}

TEST_CASE("Testing: Correct interpretation of Literal expression. -- NIL"){
    Token t(NIL, "nil", 0);
	Literal l(&t);

    CLoxInterpreter i;
    int interpretation = any_cast<int>(i.interpret(l));
    CHECK(interpretation == 0);
}

TEST_CASE("Testing: Correct interpretation of Unary expression. -- BANG"){
    Token t(FALSE, "False", 0);
    Token op(BANG, "!", 0);
	Literal l(&t);
    Unary u(&op, &l);
    CLoxInterpreter i;
    bool interpretation = any_cast<bool>(i.interpret(u));
    CHECK(interpretation);

    Token t2(TRUE, "False", 0);
    Literal l2(&t2);
    Unary u2(&op, &l2);
    interpretation = any_cast<bool>(i.interpret(u2));
    CHECK(!interpretation);
}

TEST_CASE("Testing: Correct interpretation of Unary expression. -- BANG"){
    Token t(FALSE, "False", 0);
    Token op(BANG, "!", 0);
	Literal l(&t);
    Unary u(&op, &l);
    CLoxInterpreter i;
    bool interpretation = any_cast<bool>(i.interpret(u));
    CHECK(interpretation);

    Token t2(TRUE, "False", 0);
    Literal l2(&t2);
    Unary u2(&op, &l2);
    interpretation = any_cast<bool>(i.interpret(u2));
    CHECK(!interpretation);
}

TEST_CASE("Testing: Interpreter throws error when expression value does not support BANG operator"){
    Token t(NUMBER, "5", 1);
    Token op(BANG, "!", 1);
	Literal l(&t);
    Unary u(&op, &l);
    CLoxInterpreter i;
    CHECK_THROWS_WITH(i.interpret(u), "CLoxInterpreter :: line 1 -- Right value of unary expression does not support the BANG operator.");
}

TEST_CASE("Testing: Correct interpretation of Unary expression. -- MINUS"){
    Token t(NUMBER, "989", 0);
    Token op(MINUS, "-", 0);
	Literal l(&t);
    Unary u(&op, &l);

    CLoxInterpreter i;
    double interpretation = any_cast<double>(i.interpret(u));
    CHECK(interpretation == -989);
}

TEST_CASE("Testing: Interpreter throws error when expression value does not support MINUS operator"){
    Token t(TRUE, "True", 1);
    Token op(MINUS, "-", 1);
	Literal l(&t);
    Unary u(&op, &l);
    CLoxInterpreter i;
    CHECK_THROWS_WITH(i.interpret(u), "CLoxInterpreter :: line 1 -- Right value of unary expression does not support the MINUS operator.");
}

TEST_CASE("Testing: Correct interpretation of Grouping expression."){
    Token t(NUMBER, "989", 0);
    Token op(MINUS, "-", 0);
	Literal l(&t);
    Unary u(&op, &l);
    Grouping g(&u);
    Grouping g1(&g);
    Grouping g2(&g1);

    CLoxInterpreter i;
    double interpretation = any_cast<double>(i.interpret(u));
    double interpretation2 = any_cast<double>(i.interpret(g2));
    CHECK(interpretation == interpretation2);
}
/*
TEST_CASE("Testing: Correct interpretation of Binary expression. -- <, <= , >, >= "){
    Token t1(NUMBER, "989", 0);
    Token t2(NUMBER, "989", 0);
    Token t3(NUMBER, "0", 0);
	
    Literal l1(&t1);
    Literal l2(&t2);
    Literal l3(&t3);

    Token op1(LESS, "<", 0);
    Token op2(LESS_EQUAL, "<=", 0);
    Token op3(GREATER, ">", 0);
    Token op4(GREATER_EQUAL, ">=", 0);

    Binary b1(&l1, &op1, &l2); // 989 < 989
    Binary b2(&l1, &op2, &l2); // 989 <= 989
    Binary b3(&l3, &op3, &l2); // 0 > 989
    Binary b4(&l3, &op4, &l3); // 0 >= 0
     
    CLoxInterpreter i;

    bool interpretation1 = any_cast<bool>(i.interpret(b1));
    bool interpretation2 = any_cast<bool>(i.interpret(b2));
    bool interpretation3 = any_cast<bool>(i.interpret(b3));
    bool interpretation4 = any_cast<bool>(i.interpret(b4));

    CHECK(interpretation1);
    CHECK(interpretation2);
    CHECK(interpretation3);
    CHECK(interpretation4);
}
*/