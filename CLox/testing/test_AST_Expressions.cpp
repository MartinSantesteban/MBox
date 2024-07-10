#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/AST.h"
#include "../src/token.h"

Token t(NUMBER, "100", 0);
Token t2(STRING, "ABC", 0);

Literal l1(&t);
Literal l2(&t);
Literal l3(&t2);

TEST_CASE("Testing: Correct literal == operator overload.") {	
	Grouping g1(&l1);

	CHECK(l1 == l2);
	CHECK(l2 != l3);
	CHECK(l1 != g1);
}

TEST_CASE("Testing: Correct Unary == operator overload.") {
	Token op1(BANG, "!", 0);
	Token op2(SLASH, "-", 0);
	Unary u1(&op1, &l1);
	Unary u2(&op1, &l1);
	Unary u3(&op2, &l2);
	Grouping g1(&u3);

	CHECK(u1 == u2);
	CHECK(u2 != u3);
	CHECK(g1 != u3);
}

TEST_CASE("Testing: Correct Grouping == operator overload.") {
	Grouping g1(&l1);
	Grouping g2(&l2);
	Grouping g3(&l3);

	CHECK(g1 == g2);
	CHECK(g2 != g3);
	CHECK(g1 != l3);
}

TEST_CASE("Testing: Correct Binary == operator overload.") {	
	Grouping g1(&l1);
	Grouping g2(&l2);
	Grouping g3(&l3);

	Token op1(PLUS, "+", 0);
	Token op2(SLASH, "-", 0);

	Binary b1(&l1, &op1, &l3);
	Binary b2(&l1, &op2, &l3);
	Binary b3(&l3, &op1, &l1);
	Binary b4(&l1, &op1, &l3);

	CHECK(b1 != b2);
	CHECK(b2 != b3);
	CHECK(b1 != b3);
	CHECK(b1 == b4);
}