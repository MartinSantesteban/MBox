#include "./enums_and_maps.h"
#include "./MBoxObject.h"

class MBoxEnvironment{
    public:
        MBoxEnvironment();
        MBoxEnvironment(map<string, MBoxObject*>& m);
        
        void setVariableValue(string var, MBoxObject* o);
        MBoxObject* getVariableValue(string var);
        bool isEmpty();
    private:
        std::map<string, MBoxObject*> values;   
};