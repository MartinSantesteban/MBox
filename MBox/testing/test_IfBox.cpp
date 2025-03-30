#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/MBoxParser.h"

/*
El control de flujo se maneja con las cajas. El IfBox es de las siguiente forma: 
[?: Expr que evalua a true] nombre_de_ifbox;
nombre_de_ifbox <- true branch
nombde_de_ifbox <- false branch
*/

// Cuando quieras implementar mas boxes, probablemente tengas que hacerte una supeclase box. 

bool test_parsing(vector<Token>& vt,Expr& e){
    MBoxParser p1(vt);
    Expr* res = p1.parseExpression();
    return (e == *res);
}

TEST_CASE("Testing: Correct parsing of IfBox") {
	vector<Token> tokens;
    Token t1(L_BRACE, "[", 0);
    Token t2(IF, "?", 0);
    Token t3(DOTS, ":", 0);
	Token t4(TRUE, "true", 0);
	Token t5(R_BRACE, "]", 0);

    tokens.push_back(t1);
    tokens.push_back(t2);
    tokens.push_back(t3);
	tokens.push_back(t4);
	tokens.push_back(t5);

    Literal l(&t4);
	IfBox ifBox(&l);
    CHECK(test_parsing(tokens, ifBox));
}

