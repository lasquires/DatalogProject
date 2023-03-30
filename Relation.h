#pragma once
#include "Tuple.h"
#include "Scheme.h"
#include <set>
#include <iostream>
class Relation {
private:

    set<Tuple> tuples;

public:
    string name;
    Scheme scheme;


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
    Relation join(const Relation& right);
    Tuple joinTuple(Scheme leftScheme,
                    Scheme rightScheme,
                    Tuple leftTuple,
                    Tuple rightTuple,
                    vector<string> schemeNames);
    static bool joinable(const Scheme& leftScheme,
                         const Scheme& rightScheme,
                         const Tuple& leftTuple,
                         const Tuple& rightTuple);
    bool unionize(Relation r);


};
