#pragma once
#include <vector>
#include "Parameter.h"
using namespace std;
class Predicate {
private:

public:
    string name;
    vector<Parameter> parameters;
    string toString();
    //void setName();
    //lab5:
    Predicate(string name){
        this->name = name;
    }

    Predicate();//if I take this out it breaks :'(
};
