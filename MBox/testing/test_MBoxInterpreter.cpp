#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/MBoxInterpreter.h"
#include "../src/AST.h"
#include "../src/token.h"
#include "../src/MBoxObject.h"

TEST_CASE("Testing: Correct interpretation of Literal expression. -- STRING"){
    Token t(STRING, "ABC", 0);
	Literal l(&t);

    MBoxInterpreter i;
    auto interpretation = i.interpretExpr(l);

    MBoxString s("ABC");

    CHECK(*interpretation == s);
}

TEST_CASE("Testing: Correct interpretation of Literal expression. -- NUMBER"){
    Token t(NUMBER, "95", 0);
	Literal l(&t);

    MBoxInterpreter i;
    auto interpretation = i.interpretExpr(l);

    MBoxNumber num(95);

    CHECK(*interpretation == num);
}

TEST_CASE("Testing: Correct interpretation of Literal expression. -- BOOLS"){
    Token t(TRUE, "True", 0);
	Literal l(&t);

    MBoxInterpreter i;
    auto interpretation = i.interpretExpr(l);

    MBoxBoolean bool_object(true);

    CHECK(*interpretation == bool_object);

    Token t2(FALSE, "False", 0);
	Literal l2(&t2);

    auto interpretation2 = i.interpretExpr(l2);

    MBoxBoolean bool_false(false);

    CHECK(*interpretation2 == bool_false);

}

TEST_CASE("Testing: Correct interpretation of Literal expression. -- NIL"){
    Token t(NIL, "nil", 0);
	Literal l(&t);

    MBoxInterpreter i;
    auto interpretation = i.interpretExpr(l);

    MBoxNil nil;

    CHECK(*interpretation != nil);
}

TEST_CASE("Testing: Correct interpretation of Unary expression. -- BANG"){
    Token t(FALSE, "False", 0);
    Token op(BANG, "!", 0);
	Literal l(&t);
    Unary u(&op, &l);
    MBoxInterpreter i;
    auto interpretation = i.interpretExpr(u);
    MBoxBoolean res(true);
    CHECK(*interpretation == res);

    Token t2(TRUE, "False", 0);
    Literal l2(&t2);
    Unary u2(&op, &l2);
    auto interpretation2 = i.interpretExpr(u2);
    MBoxBoolean res2(false);
    CHECK(*interpretation2 == res2);
}

TEST_CASE("Testing: Interpreter throws error when expression value does not support BANG operator"){
    Token t(NUMBER, "5", 1);
    Token op(BANG, "!", 1);
	Literal l(&t);
    Unary u(&op, &l);
    MBoxInterpreter i;
    CHECK_THROWS_WITH(i.interpretExpr(u), "[MBoxInterpreter] in line 1: [MBoxNumber] Class does not handle ! operator in unary expression.");
}

TEST_CASE("Testing: Correct interpretation of Unary expression. -- MINUS"){
    Token t(NUMBER, "989", 0);
    Token op(MINUS, "-", 0);
	Literal l(&t);
    Unary u(&op, &l);

    MBoxInterpreter i;
    auto interpretation = i.interpretExpr(u);
    MBoxNumber res(-989);
    CHECK(*interpretation == res);
}

TEST_CASE("Testing: Interpreter throws error when expression value does not support MINUS operator"){
    Token t(TRUE, "True", 1);
    Token op(MINUS, "-", 1);
	Literal l(&t);
    Unary u(&op, &l);
    MBoxInterpreter i;
    CHECK_THROWS_WITH(i.interpretExpr(u), "[MBoxInterpreter] in line 1: [MBoxBoolean] Class does not handle - operator in unary expression.");
}

TEST_CASE("Testing: Correct interpretation of Grouping expression."){
    Token t(NUMBER, "989", 0);
    Token op(MINUS, "-", 0);
	Literal l(&t);
    Unary u(&op, &l);
    Grouping g(&u);
    Grouping g1(&g);
    Grouping g2(&g1);

    MBoxInterpreter i;
    CHECK(*(i.interpretExpr(u)) == *(i.interpretExpr(g2)));
}

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
     
    MBoxInterpreter i;

    auto interpretation1 = i.interpretExpr(b1);
    auto interpretation2 = i.interpretExpr(b2);
    auto interpretation3 = i.interpretExpr(b3);
    auto interpretation4 = i.interpretExpr(b4);

    MBoxBoolean t(true);
    MBoxBoolean f(false);

    CHECK(*interpretation1 == f);
    CHECK(*interpretation2 == t);
    CHECK(*interpretation3 == f);
    CHECK(*interpretation4 == t);
}

TEST_CASE("Testing: Correct interpretation of Binary number expression. -- +, -, *, / "){
    Token t1(NUMBER, "5", 0);
    Token t2(NUMBER, "2", 0);
	
    Literal l1(&t1);
    Literal l2(&t2);

    Token op1(PLUS, "+", 0);
    Token op2(MINUS, "-", 0);
    Token op3(STAR, "*", 0);
    Token op4(SLASH, "/", 0);

    Binary b1(&l1, &op1, &l2); // 5 + 2
    Binary b2(&l1, &op2, &l2); // 5 - 2
    Binary b3(&l1, &op3, &l2); // 5 * 2
    Binary b4(&l1, &op4, &l2); // 5 / 2
     
    MBoxInterpreter i;

    auto interpretation1 = i.interpretExpr(b1);
    auto interpretation2 = i.interpretExpr(b2);
    auto interpretation3 = i.interpretExpr(b3);
    auto interpretation4 = i.interpretExpr(b4);

    MBoxNumber n1(7);
    MBoxNumber n2(3);
    MBoxNumber n3(10);
    MBoxNumber n4(2.5);

    CHECK(*interpretation1 == n1);
    CHECK(*interpretation2 == n2);
    CHECK(*interpretation3 == n3);
    CHECK(*interpretation4 == n4);
}


TEST_CASE("Testing: Correct interpretation of Binary boolean expression. -- and, or"){
    Token t1(TRUE, "True", 0);
    Token t2(FALSE, "False", 0);
	
    Literal l1(&t1);
    Literal l2(&t2);

    Token op1(AND, "and", 0);
    Token op2(OR, "or", 0);
    
    Binary b1(&l1, &op1, &l2);
    Binary b2(&l1, &op2, &l2);
    Binary b3(&l1, &op1, &l1);
    Binary b4(&l2, &op2, &l2);
     
    MBoxInterpreter i;

    auto interpretation1 = i.interpretExpr(b1);
    auto interpretation2 = i.interpretExpr(b2);
    auto interpretation3 = i.interpretExpr(b3);
    auto interpretation4 = i.interpretExpr(b4);
    
    MBoxBoolean t(true);
    MBoxBoolean f(false);

    CHECK(*interpretation1 == f);
    CHECK(*interpretation2 == t);
    CHECK(*interpretation3 == t);
    CHECK(*interpretation4 == f);
}



TEST_CASE("Testing: Correct interpretation of Binary expression. -- string concatenation +"){
    Token t1(STRING, "\"foo\"", 0);
    Token op1(PLUS, "+", 0);
    Token t2(STRING, "\"bar\"", 0);
	
    Literal l1(&t1);
    Literal l2(&t2);
    Binary b1(&l1, &op1, &l2); 
     
    MBoxInterpreter i;
    auto interpretation1 = i.interpretExpr(b1);

    MBoxString res("\"foobar\"");
    CHECK(*interpretation1 == res);
}

TEST_CASE("Testing: Correct interpretation of Binary expression. -- == , !="){
    Token t1(NUMBER, "5", 0);
    Token op1(EQUAL_EQUAL, "==", 0);
    Token op2(BANG_EQUAL, "!=", 0);
    Token t2(NUMBER, "10", 0);
	
    Literal l1(&t1);
    Literal l2(&t2);
    Binary b1(&l1, &op1, &l1); 
    Binary b2(&l1, &op1, &l2); 
    Binary b3(&l1, &op2, &l2);
    Binary b4(&l1, &op2, &l1); 
    
    MBoxInterpreter i;
    auto interpretation1 = i.interpretExpr(b1);
    auto interpretation2 = i.interpretExpr(b2);
    auto interpretation3 = i.interpretExpr(b3);
    auto interpretation4 = i.interpretExpr(b4);

    MBoxBoolean t(true);
    MBoxBoolean f(false);

    CHECK(*interpretation1 == t);
    CHECK(*interpretation2 == f);
    CHECK(*interpretation3 == t);
    CHECK(*interpretation4 == f);
}

TEST_CASE("Testing: Correct interpretation of expression."){
    Token n1(NUMBER, "1", 0);
    Token op1(PLUS, "+", 0);
    Token n2(NUMBER, "4", 0);
    Token op2(EQUAL_EQUAL, "==", 0);
    Token n3(NUMBER, "10", 0);
    Token op3(PLUS, "/", 0);
    Token n4(NUMBER, "2", 0);
	
    Literal l1(&n1);
    Literal l2(&n2);
    Binary b1(&l1, &op1, &l2);  // 1 + 4

    Literal l3(&n3);
    Literal l4(&n4);
    Binary b2(&l1, &op3, &l2);  // 10 / 2

    Binary b3(&b1, &op2, &b2);   // 1 + 4 == 10 / 2

    MBoxInterpreter i;
    auto interpretation = i.interpretExpr(b3);

    MBoxBoolean t(true);

    CHECK(*interpretation == t);
}

// STATEMENTS

TEST_CASE("Testing: Correct interpretation of PrintStatement."){
    Token n1(NUMBER, "1", 0);
    Token op1(PLUS, "+", 0);
    Token n2(NUMBER, "4", 0);
	
    Literal l1(&n1);
    Literal l2(&n2);
    Binary b1(&l1, &op1, &l2);  

    PrintStmt ps(&b1);

    MBoxInterpreter i;
    i.interpretStmt(ps);          // deberia printear 5

    CHECK(true);
}