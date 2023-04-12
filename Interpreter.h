#pragma once
#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"

//#include "Predicate.h"
class Interpreter {
private:
    DatalogProgram dlp;
    Database db;
    int passes = 0;
    bool tuplesAdded = false;
    vector<Rule> ruleNames;
    //map<int, Rule> ruleNames;
public:
    Interpreter() = default;
    explicit Interpreter(DatalogProgram dl);
    void populateDatabase();
    vector<string> paramToString(int i);
    //add queries
    void runQueries();
    void runRules(vector <int> rules, Graph g);
    Relation evaluateRule(Rule rule);
    Relation evaluatePredicate(Predicate p);
    //Relation evaluateRule(Rule ru);
    static void toString(Relation r);
    //string tostring();
    Relation unionize(Relation r);
    Predicate getFact (Rule r);
    static Graph makeGraph(const vector<Rule>& rules, bool reverse);




};
