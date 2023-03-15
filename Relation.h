#pragma once
#include "Tuple.h"
#include "Scheme.h"
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
    string toString() const; //get from predicate
    string getName();
    set<Tuple> getTuples();
    Relation select1(int index, const string& value) const;
    Relation select2(int col1, int col2) const;
    Relation project(const vector<int>& cols);
    Relation rename(vector<string> cols);
};
