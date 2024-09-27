#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../src/MBoxEnvironment.h"

TEST_CASE("Check if environment is initialized with empty values."){
    MBoxEnvironment e;
    CHECK(e.isEmpty());
}

TEST_CASE("Check if environment is no longer empty when adding variable."){
    MBoxEnvironment e;
    MBoxNumber obj(43);
    string varName = "x";
    e.setVariableValue(varName, &obj);

    CHECK(!e.isEmpty());
}

TEST_CASE("Check if variable value is set correctly."){
    MBoxEnvironment e;
    MBoxNumber obj0(43);
    MBoxNumber obj1(43);
    MBoxNumber obj2(44);
    string varName = "x";
    e.setVariableValue(varName, &obj0);

    CHECK(*e.getVariableValue(varName) == obj1);
    CHECK(*e.getVariableValue(varName) != obj2);
}

TEST_CASE("Check if variable value is set correctly."){
    MBoxEnvironment e;
    MBoxNumber obj0(43);
    MBoxNumber obj1(43);
    MBoxNumber obj2(44);
    string varName = "x";
    e.setVariableValue(varName, &obj0);

    CHECK(*e.getVariableValue(varName) == obj1);
    CHECK(*e.getVariableValue(varName) != obj2);
}

TEST_CASE("Check if error is thrown when geting undefined variable."){
    MBoxEnvironment e;
    string varName = "x";
    
    CHECK_THROWS_WITH(e.getVariableValue(varName), "[MBoxEnvironment] : x is not defined!");
}