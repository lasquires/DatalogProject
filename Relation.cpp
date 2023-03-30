#include "Relation.h"

void Relation::addTuple(const Tuple &tuple) {
    tuples.insert(tuple);
}

string Relation::toString() const {
    stringstream out;
    if (scheme.size() == 0) return "";  //this needs to be the scheme of the original
    if (tuples.empty()) return "";
    for (auto& tuple : tuples)
        out << "  " << tuple.toString(scheme) << endl;
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
    //scheme = newScheme;                       //scheme = SN
    result.scheme = newScheme;
    //new tuples/rows
    set<Tuple> newTuples;
    for (auto tuple : tuples) {
        Tuple newTuple;
        for (int i: cols)
            newTuple.values.push_back((tuple.at(i)));
        newTuples.insert(newTuple);
    }
    result.tuples = newTuples;
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

Relation Relation::join(const Relation &right) {   //joining 'right' relation to whatever relation I am in ('left')
    const Relation& left = *this;
    Scheme combinedScheme = left.scheme;
    for (const auto& rightName : right.scheme.names){
        bool inCombined = false;
        for (const auto& leftName : left.scheme.names){//TODO possible bug here
            if (rightName == leftName) inCombined = true;
        }
        if (!inCombined) combinedScheme.names.push_back(rightName);
    }
    string combinedName = "Placeholder for Rule";//TODO, change later
    Relation combinedRelation(combinedName, combinedScheme);//'cn' SnAPcG

     for (const Tuple& leftTuple : left.tuples){
         for (const Tuple& rightTuple : right.tuples){
             if (joinable(left.scheme, right.scheme, leftTuple, rightTuple)){
                 Tuple combinedTuple = joinTuple(left.scheme, right.scheme, leftTuple, rightTuple, combinedScheme.names);
                 combinedRelation.tuples.insert(combinedTuple);
             }
         }
     }
    return combinedRelation;
}





Tuple Relation::joinTuple(Scheme leftScheme, Scheme rightScheme,Tuple leftTuple, Tuple rightTuple, vector<string> schemeNames) {
    Tuple t;
    for (auto name : schemeNames) {
        for (size_t i = 0; i < leftScheme.names.size(); ++i) {
            if (leftScheme.names.at(i) == name){
                t.values.push_back(leftTuple.at(i));
            }
        }
    }
    for (size_t i = 0; i < rightScheme.names.size(); ++i) {
        bool inJoinedTuple = false;
        for (auto name : schemeNames)
            for (auto leftName : leftScheme.names){
                if (rightScheme.names.at(i) == name){
                    if (rightScheme.names.at(i) == leftName)
                        inJoinedTuple = true;
                }
            }
        if (!inJoinedTuple)
            t.values.push_back(rightTuple.at(i));
    }
    return t;
}

bool Relation::joinable(const Scheme &leftScheme, const Scheme &rightScheme, const Tuple &leftTuple,
                        const Tuple &rightTuple) {
    bool canJoin = true;
    for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
        const string& leftName = leftScheme.at(leftIndex);
        const string& leftValue = leftTuple.at(leftIndex);
        //cout << "left name: " << leftName << " value: " << leftValue << endl;
        for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
            const string& rightName = rightScheme.at(rightIndex);
            const string& rightValue = rightTuple.at(rightIndex);
            //cout << "right name: " << rightName << " value: " << rightValue << endl;
            if (rightName == leftName && rightValue != leftValue) {
                canJoin = false;
            }
        }
    }
    return canJoin;

}

bool Relation::unionize(Relation r) {
    bool tupleAdded = false;
        for (auto tuple : r.getTuples()) {
            if(tuples.insert(tuple).second){//if a ble to insert tuple into tuples-> true
                cout << "  " << tuple.toString(scheme) << endl;
                tupleAdded = true;

            }
        }
    //Scheme s = it->second.scheme;
    //r.scheme = it->second.scheme;
    //Scheme ss = r.scheme;
    return tupleAdded;
}
