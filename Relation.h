#pragma once
#include "Tuple.h"
#include <set>
class Relation {
private:

    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:

    Relation(const string& name, const Scheme& scheme)
            : name(name), scheme(scheme) { }

    void addTuple(const Tuple& tuple);
    string toString() const;
    Relation select(int index, const string& value) const;
};
