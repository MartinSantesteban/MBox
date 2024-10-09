#include "./MBoxEnvironment.h"

MBoxEnvironment::MBoxEnvironment(){
    this->values = std::map<string, MBoxObject*>();
}

MBoxEnvironment::MBoxEnvironment(map<string, MBoxObject*>& m){
    this->values = m;
}

void MBoxEnvironment::setVariableValue(string var, MBoxObject* o){
    this->values[var] = o;
}

void MBoxEnvironment::redefineVariableValue(string var, MBoxObject* o){
    if(this->values.count(var) == 0){
        throw invalid_argument("[MBoxEnvironment] : " + var + " is not a defined variable.");
    }
    this->values[var] = o;
}

MBoxObject* MBoxEnvironment::getVariableValue(string var){
    if(this->values.count(var) == 0){
        throw invalid_argument("[MBoxEnvironment] : " + var + " is not a defined variable.");
    }
    return this->values[var];
}

bool MBoxEnvironment::isEmpty(){
    return this->values.empty();
}