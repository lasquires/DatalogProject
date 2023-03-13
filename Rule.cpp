//
// Created by lukes on 2/12/2023.
//

#include "Rule.h"

string Rule::toString() {
    string output = headPredicate.toString() + " :- ";
    for (size_t i = 0; i < predicates.size(); i++) {
        output += predicates[i].toString();
        if (i < predicates.size() - 1) {
            output += ",";
        }
    }
    output += ".";
    return output;
}
