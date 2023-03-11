#pragma once
#include "Predicate.h"

class Rule {
public:
    Predicate headPredicate;
    vector<Predicate> predicates;
    string toString();
};
