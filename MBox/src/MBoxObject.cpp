#include "MBoxObject.h"

// -------------------- MBoxNumber -----------------------                           

MBoxNumber::MBoxNumber(double d){
    this->value = d;
}

MBoxObject* MBoxNumber::handleMinus(){
    this->value = this->value * (-1);
    return this;
}

MBoxObject* MBoxNumber::handleLess(MBoxObject* right){
    return right->isGreaterThanNumber(this);
}

MBoxObject* MBoxNumber::isGreaterThanNumber(MBoxNumber* left){
    return new MBoxBoolean(left->value < this->value);            // cambiar a que sea por referencia? this->value := ...
}

MBoxObject* MBoxNumber::handleLessEq(MBoxObject* right){
    return right->isGreaterEqualThanNumber(this);
}

MBoxObject* MBoxNumber::isGreaterEqualThanNumber(MBoxNumber* left){
    return new MBoxBoolean(left->value <= this->value);
}

MBoxObject* MBoxNumber::handleGreater(MBoxObject* right){
    return right->handleLess(this);
}

MBoxObject* MBoxNumber::handleGreaterEq(MBoxObject* right){
    return right->handleLessEq(this);
}

MBoxObject* MBoxNumber::handlePlus(MBoxObject* right){
    return right->getAddedToNumber(this);
}

MBoxObject* MBoxNumber::getAddedToNumber(MBoxNumber* left){
    return new MBoxNumber(left->value + this->value);
}

MBoxObject* MBoxNumber::handleMinus(MBoxObject* right){
    return right->getSubstractedToNumber(this);
}

MBoxObject* MBoxNumber::getSubstractedToNumber(MBoxNumber* left){
    return new MBoxNumber(left->value - this->value);
}

MBoxObject* MBoxNumber::handleStar(MBoxObject* right){
    return right->getMultipliedToNumber(this);
}

MBoxObject* MBoxNumber::getMultipliedToNumber(MBoxNumber* left){
    return new MBoxNumber(left->value * this->value);
}

MBoxObject* MBoxNumber::handleSlash(MBoxObject* right){
    return right->getDividedToNumber(this);
}

MBoxObject* MBoxNumber::getDividedToNumber(MBoxNumber* left){
    return new MBoxNumber(left->value / this->value);
}

// -------------------- MBoxString ----------------------

MBoxString::MBoxString(string s){
    this->value = s;
}

MBoxObject* MBoxString::handlePlus(MBoxObject* right_object){
    return right_object->getAddedToString(this);
}

MBoxObject* MBoxString::getAddedToString(MBoxString* left_string){
    return new MBoxString(left_string->value + this->value);
}

// -------------------- MBoxNil -------------------------

MBoxNil::MBoxNil(){}

// -------------------- MBoxBoolean ------------------------

MBoxBoolean::MBoxBoolean(bool b){
    this->value = b;
}

MBoxObject* MBoxBoolean::handleBang(){
    return new MBoxBoolean(!this->value);
}

MBoxObject* MBoxBoolean::handleAnd(MBoxObject* right_object){
    return right_object->andBoolean(this);
}

MBoxObject* MBoxBoolean::andBoolean(MBoxBoolean* left_bool){
    return new MBoxBoolean(left_bool->value && this->value);
}

MBoxObject* MBoxBoolean::handleOr(MBoxObject* right_object){
    return right_object->orBoolean(this);
}

MBoxObject* MBoxBoolean::orBoolean(MBoxBoolean* left_bool){
    return new MBoxBoolean(left_bool->value || this->value);
}