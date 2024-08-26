#ifndef MBOX_OBJECT_H
#define MBOX_OBJECT_H

#include "enums_and_maps.h"

class MBoxNumber;
class MBoxBoolean;
class MBoxString;

class MBoxObject{
    public: 
        ~MBoxObject() = default;

        //virtual MBoxObject* handleEq(MBoxObject* right);
        //virtual MBoxObject* handelNeq(MBoxObject* right);
        
        virtual MBoxObject* handleLess(MBoxObject* right_object){};
        virtual MBoxObject* handleLessEq(MBoxObject* right_object){};
        virtual MBoxObject* handleGreater(MBoxObject* right_object){};
        virtual MBoxObject* handleGreaterEq(MBoxObject* right_object){};
        virtual MBoxObject* handlePlus(MBoxObject* right_object){};
        virtual MBoxObject* handleMinus(MBoxObject* right_object){};
        virtual MBoxObject* handleStar(MBoxObject* right_object){};
        virtual MBoxObject* handleSlash(MBoxObject* right_object){};
        virtual MBoxObject* handleAnd(MBoxObject* right_object){};
        virtual MBoxObject* handleOr(MBoxObject* right_object){};
        virtual MBoxObject* handleBang(){};
        virtual MBoxObject* handleMinus(){};

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
        friend ostream& operator<< (ostream &out, const MBoxNumber& o);

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
        friend ostream& operator<< (ostream &out, const MBoxString& o);

        MBoxObject* handlePlus(MBoxObject* right_object);

        MBoxObject* getAddedToString(MBoxString* left_string);

        string value;
};

class MBoxNil : public MBoxObject{
    public: 
        MBoxNil();
        friend ostream& operator<< (ostream &out, const MBoxNil& o);
};

class MBoxBoolean : public MBoxObject{
    public:
        MBoxBoolean(bool b);
        friend ostream& operator<< (ostream &out, const MBoxBoolean& o);

        
        MBoxObject* handleBang();
        MBoxObject* handleAnd(MBoxObject* right_object);
        MBoxObject* handleOr(MBoxObject* right_object);

        MBoxObject* andBoolean(MBoxBoolean* left_bool);
        MBoxObject* orBoolean(MBoxBoolean* left_bool);

        bool value;

};

#endif