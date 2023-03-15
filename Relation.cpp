#include "Relation.h"

void Relation::addTuple(const Tuple &tuple) {
    tuples.insert(tuple);
}

string Relation::toString() const {
    stringstream out;
    if (scheme.size() == 0) return "";
    if (tuples.empty()) return "";
    for (auto& tuple : tuples)
        out << tuple.toString(scheme) << endl;
    return out.str();
}

Relation Relation::select1(int index, const string &value) const {
    Relation result(name, scheme);
    // add tuples to the result if they meet the condition
    for (auto& tuple : tuples){                    //i = tuples.begin(); i != tuples.end(); i++){
        if (tuple.at(index) == value) result.addTuple(tuple);
    }
    return result;
}

Relation Relation::select2(int col1, int col2) const {
    Relation result(name, scheme);
    for (auto& tuple : tuples){
        if (tuple.at(col1) == tuple.at(col2)) result.addTuple(tuple);
    }
    return result;
}

Relation Relation::project(const vector<int>& cols) {//cols is indeces of columns/schemes that are being projected
    //create new scheme/header  ^^^^[0,1]     scheme = SNAP
    Relation result(name, scheme);
    vector<string> newScheme;
    for(int i : cols)
        newScheme.push_back(scheme.at(i));  //SN
    scheme = newScheme;                       //scheme = SN

    //new tuples/rows
    set<Tuple> newTuples;
    for (auto tuple : tuples) {
        Tuple newTuple;
        for (int i: cols)
            newTuple.values.push_back((tuple.at(i)));
        newTuples.insert(newTuple);
    }
    tuples = newTuples;
    return result;
}

Relation Relation::rename(vector<string> cols) {
    Relation result(name, scheme);
    for (size_t i = 0; i < cols.size(); i++)
        scheme.names.at(i) = cols.at(i);
    return result;
}

set<Tuple> Relation::getTuples() {
    return tuples;
}

string Relation::getName() {
    return name;
}
