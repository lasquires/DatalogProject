#pragma once

#include <set>
#include "Rule.h"


class DatalogProgram {
private:

public:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    set<string> domain;
    void addScheme(Predicate scheme);
    void addFact(Predicate fact);
    void addRule(Rule rule);
    void addQuery(Predicate query);
    void addDomain();
    string toString();
};
