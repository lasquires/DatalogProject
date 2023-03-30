#pragma once
#include "DatalogProgram.h"
#include "Database.h"
//#include "Predicate.h"
class Interpreter {
private:
    DatalogProgram dlp;
    Database db;
    int passes = 0;
    bool tuplesAdded = false;
public:
    Interpreter() = default;
    explicit Interpreter(DatalogProgram dl);
    void populateDatabase();
    vector<string> paramToString(int i);
    //add queries
    void runQueries();
    void runRules();
    Relation evaluateRule(Rule rule);
    Relation evaluatePredicate(Predicate p);
    //Relation evaluateRule(Rule ru);
    static void toString(Relation r);
    //string tostring();
    Relation unionize(Relation r);
    Predicate getFact (Rule r);


};
