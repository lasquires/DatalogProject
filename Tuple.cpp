//
// Created by lukes on 3/7/2023.
//

#pragma once
#include "Tuple.h"

unsigned Tuple::size() const {
    return values.size();
}

const string &Tuple::at(int index) const {
    return values.at(index);
}

bool Tuple::operator<(const Tuple t) const {
    return values < t.values;
}

string Tuple::toString(const Scheme &scheme) const {
    const Tuple& tuple = *this;
    stringstream out;
    for (size_t i = 0; i< scheme.size(); ++i){
        out << scheme.at(i) << "=" << tuple.at(i);
        if (i != scheme.size() - 1) out << ", ";
    }
    // fix the code to print "name=value" pairs
//    out << scheme.size();
//    out << scheme.at(0);
//    out << tuple.size();
//    out << tuple.at(0);
    return out.str();
}
