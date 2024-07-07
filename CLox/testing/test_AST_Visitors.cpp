#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/AST.h"
#include "../src/visitor.h"
#include "../src/token.h"

Printer p;

TEST_CASE("Testing: Printer - Correct Literal print") {
	Token t(STRING, "ABC", 0);
	Literal l(&t);

	Token t2(NUMBER, "4", 0);
	Literal l2(&t2);
	
	CHECK(p.visit(l) == "ABC");
	CHECK(p.visit(l2) == "4");
}

TEST_CASE("Testing: Printer - Correct Unary print") {
	Token t(STRING, "ABC", 0);
	Literal l(&t);
	Token t2(BANG, "!", 0);
	Unary u(&t2, &l);
	CHECK(p.visit(u) == "!ABC");

	Token t3(NUMBER, "5", 0);
	Literal l2(&t3);
	Token t4(SLASH, "-", 0);
	Unary u2(&t4, &l2);
	CHECK(p.visit(u2) == "-5");
}

TEST_CASE("Testing: Printer - Correct Binary print") {
	Token t1(NUMBER, "5", 0);
	Token t2(NUMBER, "2", 0);

	Literal l1(&t1);
	Literal l2(&t2);

	Token o1(PLUS, "+", 0);
	Token o2(PLUS, "-", 0);
	Token o3(PLUS, "*", 0);

	Binary b1(&l1, &o1, &l2);
	Binary b2(&l1, &o2, &l2);
	Binary b3(&l1, &o3, &l2);

	CHECK(p.visit(b1) == "+ (5) (2)");
	CHECK(p.visit(b2) == "- (5) (2)");
	CHECK(p.visit(b3) == "* (5) (2)");
}

TEST_CASE("Testing: Printer - Correct Grouping print") {
	Token t(STRING, "ABC", 0);
	Literal l(&t);
	Grouping g(&l);
	CHECK(p.visit(g) == "group ABC");

	Token t2(NUMBER, "5", 0);
	Literal l2(&t2);
	Grouping g2(&l2);
	CHECK(p.visit(g2) == "group 5");
}

TEST_CASE("Testing: Printer - Proof of fire") {
	Token t1(NUMBER, "100", 0);
	Literal l1(&t1);
	Token o1(SLASH, "-", 0);
	Unary u1(&o1, &l1);
	Grouping g1(&u1);
	Token t2(STRING, "ABC", 0);
	Literal l2(&t2);
	Grouping g2(&l2);
	
	Token o3(PLUS, "+", 0);
	Binary b(&g1, &o3, &g2);

	CHECK(p.visit(b) == "+ (group -100) (group ABC)");
}
