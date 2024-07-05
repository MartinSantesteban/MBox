#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/AST.h"
#include "../src/visitor.h"
#include "../src/token.h"

TEST_CASE("Testing: Printer - Correct Literal print") {
	Printer p;
	Token t(STRING, "ABC", 0);
	Literal l(&t);
	CHECK(p.visit(l) == "ABC");
}



