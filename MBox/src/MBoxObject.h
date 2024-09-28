#ifndef MBOX_OBJECT_H
#define MBOX_OBJECT_H

#include "enums_and_maps.h"

class MBoxNumber;
class MBoxBoolean;
class MBoxString;

class MBoxObject{
    public: 
        virtual ~MBoxObject() = default;
        void throw_exception(string s){throw invalid_argument("[" + this->className() + "] " + s);};
        bool operator==(MBoxObject& r);
        bool operator!=(MBoxObject& r);
        virtual bool _equals(MBoxObject& right);
        virtual string className(){return "MBoxObject";};
        virtual void print();

        virtual MBoxObject* handleEq(MBoxObject* right);
        virtual MBoxObject* handleNeq(MBoxObject* right);
        virtual MBoxObject* handleLess(MBoxObject* right_object){throw_exception("Class does not handle < operator in binary expression.");};
        virtual MBoxObject* handleLessEq(MBoxObject* right_object){throw_exception("Class does not handle <= operator in binary expression.");};
        virtual MBoxObject* handleGreater(MBoxObject* right_object){throw_exception("Class does not handle > operator in binary expression.");};
        virtual MBoxObject* handleGreaterEq(MBoxObject* right_object){throw_exception("Class does not handle >= operator in binary expression.");};
        virtual MBoxObject* handlePlus(MBoxObject* right_object){throw_exception("Class does not handle + operator in binary expression.");};
        virtual MBoxObject* handleMinus(MBoxObject* right_object){throw_exception("Class does not handle - operator in binary expression.");};
        virtual MBoxObject* handleStar(MBoxObject* right_object){throw_exception("Class does not handle * operator in binary expression.");};
        virtual MBoxObject* handleSlash(MBoxObject* right_object){throw_exception("Class does not handle / operator in binary expression.");};
        virtual MBoxObject* handleAnd(MBoxObject* right_object){throw_exception("Class does not handle AND operator in binary expression.");};
        virtual MBoxObject* handleOr(MBoxObject* right_object){throw_exception("Class does not handle OR operator in binary expression.");};
        virtual MBoxObject* handleBang(){throw_exception("Class does not handle ! operator in unary expression.");};
        virtual MBoxObject* handleMinus(){throw_exception("Class does not handle - operator in unary expression.");};

        virtual MBoxObject* isGreaterThanNumber(MBoxNumber* left_number){throw_exception("Class cant be compared to number.");};
        virtual MBoxObject* isGreaterEqualThanNumber(MBoxNumber* left_number){throw_exception("Class cant be compared to number.");};
        virtual MBoxObject* getAddedToNumber(MBoxNumber* left_number){throw_exception("Class cant be added (+) to number.");};
        virtual MBoxObject* getSubstractedToNumber(MBoxNumber* left_number){throw_exception("Class cant be substracted (-) to number.");};
        virtual MBoxObject* getMultipliedToNumber(MBoxNumber* left_number){throw_exception("Class cant be multiplied (*) to number.");};
        virtual MBoxObject* getDividedToNumber(MBoxNumber* left_number){throw_exception("Class cant be dividided (/) to number.");};
        
        virtual MBoxObject* getAddedToString(MBoxString* left_string){{throw_exception("Class does not support + operation with string.");};};
        
        virtual MBoxObject* andBoolean(MBoxBoolean* left_bool){{throw_exception("Class does not support AND operation with string.");};};
        virtual MBoxObject* orBoolean(MBoxBoolean* left_bool){{throw_exception("Class does not support OR operation with string.");};};
};

class MBoxNumber : public MBoxObject{
    public:
        MBoxNumber(double d);
        ~MBoxNumber() = default;
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
    private:
        double value;
};

class MBoxString : public MBoxObject{
    public: 
        MBoxString(string s);
        ~MBoxString() = default;
        string className();
        void print();

        bool _equals(MBoxObject& right);

        MBoxObject* handlePlus(MBoxObject* right_object);

        MBoxObject* getAddedToString(MBoxString* left_string);
    private:
        string value;
};

class MBoxNil : public MBoxObject{
    public: 
        MBoxNil();
        ~MBoxNil() = default;
        string className();
        void print();
        bool _equals(MBoxObject& right);
};

class MBoxBoolean : public MBoxObject{
    public:
        MBoxBoolean(bool b);
        ~MBoxBoolean() = default;
        void print();
        string className();

        bool _equals(MBoxObject& right);
        
        MBoxObject* handleBang();
        MBoxObject* handleAnd(MBoxObject* right_object);
        MBoxObject* handleOr(MBoxObject* right_object);

        MBoxObject* andBoolean(MBoxBoolean* left_bool);
        MBoxObject* orBoolean(MBoxBoolean* left_bool);
    private:
        bool value;
};

#endif