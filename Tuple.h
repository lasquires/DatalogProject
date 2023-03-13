#pragma once
#include "Scheme.h"

class Tuple {
private:

    vector<string> values;

public:

    Tuple(vector<string> values) : values(values) { }
    unsigned size() const;
    const string& at(int index) const;

    bool operator<(const Tuple t) const;
    string toString(const Scheme& scheme) const;
    // TODO: add more delegation functions as needed
};
