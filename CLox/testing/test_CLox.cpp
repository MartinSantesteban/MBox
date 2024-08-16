#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/CLox.h"

TEST_CASE("Testing: Lexer using valid/invalid parameters") {
	CLox cl;
	const char* p0 = "CLoxMain (nombre del ejecutable)";
	const char* p1 = "testing/testing_code/prueba_input_lexer";
	const char* p2 = "otra cosa";
	cout << "aca" << endl;
	//const char* parameters0[] = {};	No puedo hacer tdd sobre el repl todavia
    //CHECK(cl.scan(sizeof(parameters0)/sizeof(parameters0[0]) ,parameters0) == 0);
	
	const char* parameters1[] = {p0,p1};
    CHECK(cl.scan(sizeof(parameters1)/sizeof(parameters1[1]) ,parameters1) == 0);
	const char* parameters2[] = {p0,p1,p2};
    CHECK(cl.scan(sizeof(parameters2)/sizeof(parameters2[0]) ,parameters2) == -1);
}

TEST_CASE("Testing: Compiler starts without error."){
	CLox cl;
	CHECK(!cl.codeHadError());
}

TEST_CASE("Testing: Compiler throws correct error && switches hadError"){
	CLox cl;
	CHECK(cl.error(1,"error trial") == "[line 1] Error: error trial");
	CHECK(cl.codeHadError());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                     TDD del pipeline codigo src -> lexer -> parser -> Interprete.                         //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Interpreter returns correct program value. -- arithmetic operations"){
	const char* p0 = "CLoxMain (nombre del ejecutable)";
	const char* p1 = "./testing/testing_code/arithmetic_operations_test";
	const char* parameters1[] = {p0,p1};
	CLox cl;
	// aca hay que testear que se printee el valor correcto :: Result of execution: 32
    CHECK(cl.scan(sizeof(parameters1)/sizeof(parameters1[1]) ,parameters1) == 0);
}

TEST_CASE("Interpreter returns correct program value. -- string operations"){
	const char* p0 = "CLoxMain (nombre del ejecutable)";
	const char* p1 = "./testing/testing_code/string_operations_test";
	const char* parameters1[] = {p0,p1};
	CLox cl;
	// aca hay que testear que se printee el valor correcto :: Result of execution: "FOOBAR"
    CHECK(cl.scan(sizeof(parameters1)/sizeof(parameters1[1]) ,parameters1) == 0);
}


TEST_CASE("Interpreter returns correct program value. -- comparisons"){
	const char* p0 = "CLoxMain (nombre del ejecutable)";
	const char* p1 = "./testing/testing_code/comparison_operations_test";
	const char* parameters1[] = {p0,p1};
	CLox cl;
	// aca hay que testear que se printee el valor correcto :: Result of execution: True
    CHECK(cl.scan(sizeof(parameters1)/sizeof(parameters1[1]) ,parameters1) == 0);
}

