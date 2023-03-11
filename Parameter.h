#pragma once
#include <string>
#include "Token.h"
using namespace std;

class Parameter {
public:
    string value; //string or ID
    bool isString = false;
    string toString();
};
