#pragma once
#include <vector>
#include "Parameter.h"
using namespace std;
class Predicate {
public:
    string name;
    vector<Parameter> parameters;
    string toString();
    //void setName();
};
