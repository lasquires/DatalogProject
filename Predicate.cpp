#include "Predicate.h"

string Predicate::toString() {
    string output = name + "(";
    for (size_t i = 0; i < parameters.size(); i++) {
        output += parameters.at(i).toString();
        if (i < parameters.size() - 1) {
            output += ",";
        }
    }
    output += ")";
    return output;
}

Predicate::Predicate() {
    return;
}

//void Predicate::setName() {
//
//}

