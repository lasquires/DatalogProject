#include "Relation.h"

void Relation::addTuple(const Tuple &tuple) {
    tuples.insert(tuple);
}

string Relation::toString() const {
    stringstream out;
    for (auto& tuple : tuples)
        out << tuple.toString(scheme) << endl;
    return out.str();
}

Relation Relation::select(int index, const string &value) const {
    Relation result(name, scheme);
    // add tuples to the result if they meet the condition
    for (auto& tuple : tuples){                    //i = tuples.begin(); i != tuples.end(); i++){
        if (tuple.at(index) == value) result.addTuple(tuple);
    }
    return result;
}
