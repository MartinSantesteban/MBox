#include "MBoxObject.h"

// -------------------- MBoxObject -----------------------                           

bool MBoxObject::operator==(MBoxObject& right){
    return this->_equals(right);
}

bool MBoxObject::operator!=(MBoxObject& right){
    return !(this->_equals(right));
}

bool MBoxObject::_equals(MBoxObject& right){
    return typeid(*this) == typeid(right);
}

MBoxObject* MBoxObject::handleEq(MBoxObject* right){
    if(*this == *right) return new MBoxBoolean(true);
    return new MBoxBoolean(false);
}

MBoxObject* MBoxObject::handleNeq(MBoxObject* right){
    if(*this != *right) return new MBoxBoolean(true);
    return new MBoxBoolean(false);
}

void MBoxObject::print(){
    cout << "[" << this->className() << "]" << endl;
}

// -------------------- MBoxNumber -----------------------                           

MBoxNumber::MBoxNumber(double d){
    this->value = d;
}

string MBoxNumber::className(){
    return "MBoxNumber";
}

void MBoxNumber::print(){
    cout << "[" << this->className() << " " << this->value << "]";
}

MBoxObject* MBoxNumber::handleMinus(){
    //this->value *= -1;
    //return this;
    return new MBoxNumber(this->value * -1);
}

MBoxObject* MBoxNumber::handleLess(MBoxObject* right){
    return right->isGreaterThanNumber(this);
}

MBoxObject* MBoxNumber::isGreaterThanNumber(MBoxNumber* left){
    return new MBoxBoolean(left->value < this->value);            
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

bool MBoxNumber::_equals(MBoxObject& right){
    if(typeid(*this) != typeid(right)) return false;
    auto right_number = static_cast<MBoxNumber &>(right);
    return this->value == right_number.value;
}

// -------------------- MBoxString ----------------------

MBoxString::MBoxString(string s){
    this->value = s;
}

void MBoxString::print(){
    cout << "[" << this->className() << " " << this->value << "]";
}

string MBoxString::className(){
    return "MBoxString";
}

MBoxObject* MBoxString::handlePlus(MBoxObject* right_object){
    return right_object->getAddedToString(this);
}

MBoxObject* MBoxString::getAddedToString(MBoxString* left_string){
    string left = left_string->value;
    left.erase(left.size()-1);
    string right = this->value;
    right.erase(0,1);
    return new MBoxString(left + right);
}

bool MBoxString::_equals(MBoxObject& right){
    if(typeid(*this) != typeid(right)) return false;
    auto right_number = static_cast<MBoxString &>(right);
    return this->value == right_number.value;
}

// -------------------- MBoxNil -------------------------

MBoxNil::MBoxNil(){}

string MBoxNil::className(){
    return "MBoxNil";
}

void MBoxNil::print(){
    cout << "[" << this->className() << "]";
}

bool MBoxNil::_equals(MBoxObject& right){
    return false;
}

// -------------------- MBoxBoolean ------------------------

MBoxBoolean::MBoxBoolean(bool b){
    this->value = b;
}

string MBoxBoolean::className(){
    return "MBoxBoolean";
}

void MBoxBoolean::print(){
    string p_string = (this->value)? "True" : "False";
    cout << "[" << this->className() << " " << p_string << "]";
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

bool MBoxBoolean::_equals(MBoxObject& right){
    if(typeid(*this) != typeid(right)) return false;
    auto right_number = static_cast<MBoxBoolean &>(right);
    return this->value == right_number.value;
}