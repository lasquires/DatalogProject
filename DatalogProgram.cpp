#include "DatalogProgram.h"

string DatalogProgram::toString() {
    string output = "Success!\n";
    output += "Schemes(" + to_string(schemes.size()) + "):\n";
    for (auto & scheme : schemes) {
        output += "  " + scheme.toString() + "\n";
    }
    output += "Facts(" + to_string(facts.size()) + "):\n";
    for (auto & fact : facts) {
        output += "  " + fact.toString() + ".\n";
    }
    output += "Rules(" + to_string(rules.size()) + "):\n";
    for (auto & rule : rules) {
        output += "  " + rule.toString() + "\n";
    }
    output += "Queries(" + to_string(queries.size()) + "):\n";
    for (auto & query : queries) {
        output += "  " + query.toString() + "?\n";
    }
    output += "Domain(" + to_string(domain.size()) + "):\n";
    for (auto & i : domain) {       //(int i = 0; i < domain.size(); i++)
        output += "  " + i + "\n";
    }
    return output;

}

void DatalogProgram::addScheme(Predicate scheme) {
    schemes.push_back(scheme);
}

void DatalogProgram::addFact(Predicate fact) {
    facts.push_back(fact);
}

void DatalogProgram::addRule(Rule rule) {
    rules.push_back(rule);
}

void DatalogProgram::addQuery(Predicate query) {
    queries.push_back(query);
}

void DatalogProgram::addDomain() {

}



