#ifndef MBOX_OBJECT_H
#define MBOX_OBJECT_H

#include "enums_and_maps.h"

class MBoxNumber;
class MBoxBoolean;
class MBoxString;

class MBoxObject{
    public: 
        ~MBoxObject() = default;

        bool operator==(MBoxObject& r);
        bool operator!=(MBoxObject& r);
        virtual bool _equals(MBoxObject& right);
        virtual string className(){return "MBoxObject";};
        virtual void print();

        virtual MBoxObject* handleEq(MBoxObject* right);
        virtual MBoxObject* handleNeq(MBoxObject* right);
        virtual MBoxObject* handleLess(MBoxObject* right_object){throw invalid_argument("[" + this->className() + "] Class does not handle > operator in binary expression.");};
        virtual MBoxObject* handleLessEq(MBoxObject* right_object){throw invalid_argument("[" + this->className() + "] Class does not handle >= operator in binary expression.");};
        virtual MBoxObject* handleGreater(MBoxObject* right_object){throw invalid_argument("[" + this->className() + "] Class does not handle < operator in binary expression.");};
        virtual MBoxObject* handleGreaterEq(MBoxObject* right_object){throw invalid_argument("[" + this->className() + "] Class does not handle <= operator in binary expression.");};
        virtual MBoxObject* handlePlus(MBoxObject* right_object){throw invalid_argument("[" + this->className() + "] Class does not handle + operator in binary expression.");};
        virtual MBoxObject* handleMinus(MBoxObject* right_object){throw invalid_argument("[" + this->className() + "] Class does not handle - operator in binary expression.");};
        virtual MBoxObject* handleStar(MBoxObject* right_object){throw invalid_argument("[" + this->className() + "] Class does not handle * operator in binary expression.");};
        virtual MBoxObject* handleSlash(MBoxObject* right_object){throw invalid_argument("[" + this->className() + "] Class does not handle / operator in binary expression.");};
        virtual MBoxObject* handleAnd(MBoxObject* right_object){throw invalid_argument("[" + this->className() + "] Class does not handle AND operator in binary expression.");};
        virtual MBoxObject* handleOr(MBoxObject* right_object){throw invalid_argument("[" + this->className() + "] Class does not handle OR operator in binary expression.");};
        virtual MBoxObject* handleBang(){throw invalid_argument("[" + this->className() + "] Class does not handle ! operator in unary expression.");};
        virtual MBoxObject* handleMinus(){throw invalid_argument("[" + this->className() + "] Class does not handle - operator in unary expression.");};

        virtual MBoxObject* isGreaterThanNumber(MBoxNumber* left_number){};
        virtual MBoxObject* isGreaterEqualThanNumber(MBoxNumber* left_number){};
        virtual MBoxObject* getAddedToNumber(MBoxNumber* left_number){};
        virtual MBoxObject* getSubstractedToNumber(MBoxNumber* left_number){};
        virtual MBoxObject* getMultipliedToNumber(MBoxNumber* left_number){};
        virtual MBoxObject* getDividedToNumber(MBoxNumber* left_number){};
        
        virtual MBoxObject* getAddedToString(MBoxString* left_string){};
        
        virtual MBoxObject* andBoolean(MBoxBoolean* left_bool){};
        virtual MBoxObject* orBoolean(MBoxBoolean* left_bool){};
};

class MBoxNumber : public MBoxObject{
    public:
        MBoxNumber(double d);
        void print();

        string className();
        bool _equals(MBoxObject& right);

        MBoxObject* handleLess(MBoxObject* right_object);
        MBoxObject* handleLessEq(MBoxObject* right_object);
        MBoxObject* handleGreater(MBoxObject* right_object);
        MBoxObject* handleGreaterEq(MBoxObject* right_object);
        MBoxObject* handlePlus(MBoxObject* right_object);
        MBoxObject* handleMinus(MBoxObject* right_object);
        MBoxObject* handleStar(MBoxObject* right_object);
        MBoxObject* handleSlash(MBoxObject* right_object);
        MBoxObject* handleMinus();

        MBoxObject* isGreaterThanNumber(MBoxNumber* left_number);
        MBoxObject* isGreaterEqualThanNumber(MBoxNumber* left_number);
        MBoxObject* getAddedToNumber(MBoxNumber* left_number);
        MBoxObject* getSubstractedToNumber(MBoxNumber* left_number);
        MBoxObject* getMultipliedToNumber(MBoxNumber* left_number);
        MBoxObject* getDividedToNumber(MBoxNumber* left_number);

        double value;
};

class MBoxString : public MBoxObject{
    public: 
        MBoxString(string s);
        string className();
        void print();

        bool _equals(MBoxObject& right);

        MBoxObject* handlePlus(MBoxObject* right_object);

        MBoxObject* getAddedToString(MBoxString* left_string);

        string value;
};

class MBoxNil : public MBoxObject{
    public: 
        MBoxNil();
        string className();
        void print();
        bool _equals(MBoxObject& right);
};

class MBoxBoolean : public MBoxObject{
    public:
        MBoxBoolean(bool b);
        void print();
        string className();

        bool _equals(MBoxObject& right);
        
        MBoxObject* handleBang();
        MBoxObject* handleAnd(MBoxObject* right_object);
        MBoxObject* handleOr(MBoxObject* right_object);

        MBoxObject* andBoolean(MBoxBoolean* left_bool);
        MBoxObject* orBoolean(MBoxBoolean* left_bool);

        bool value;
};

#endif