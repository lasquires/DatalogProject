#pragma once
#include "Scheme.h"

class Tuple {
private:

public:
    vector<string> values;

    Tuple(vector<string> values) : values(values) { }
    unsigned size() const;
    Tuple(){}

    const string& at(int index) const;

    bool operator<(const Tuple t) const;
    string toString(const Scheme& scheme) const;

    // TODO: add more delegation functions as needed
};
