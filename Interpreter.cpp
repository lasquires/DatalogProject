//
// Created by lukes on 3/13/2023.
//

#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram dl) {
    dlp = dl;
    populateDatabase();
    cout << "Rule Evaluation" << endl;
    runRules();
    cout << "\nSchemes populated after " << passes << " passes through the Rules.\n" << endl;
    runQueries();
}

void Interpreter::populateDatabase() {
    for(size_t i = 0; i < dlp.schemes.size(); i++){
        Predicate scheme = dlp.schemes.at(i);
        Relation r = Relation(scheme.name, paramToString(i));
        string name = scheme.name;
        vector<Parameter> schema = scheme.parameters;
        db.addRelation(scheme.name, r);
    }
    for (const Predicate& fact : dlp.facts){
        vector<string> tuple;
        for (const Parameter& param : fact.parameters){
            tuple.push_back(param.value);
        }
        db.relationDict.at(fact.name).addTuple(tuple);
    }


}

void Interpreter::runRules() {
    passes += 1;
    tuplesAdded = false;
    for (auto rule : dlp.rules) {
        cout << rule.toString() << endl;
        Relation r = db.relationDict.at(rule.headPredicate.name);
        evaluateRule(rule);
    }
    if (tuplesAdded)
        runRules();
}
Relation Interpreter::evaluateRule(Rule rule) {
    Relation r = evaluatePredicate(rule.predicates.at(0));
    r.name = rule.headPredicate.name;
    string name = r.name;
    for (unsigned int i = 1; i < rule.predicates.size(); i++) {//auto predicate : rule.predicates){
        r = r.join(evaluatePredicate(rule.predicates.at(i)));
    }
    vector<int> toProj;
    for (auto param: rule.headPredicate.parameters) {
        for (unsigned int i = 0; i < r.scheme.names.size(); i++) {
            if (param.value == r.scheme.names.at(i)) {
                toProj.push_back(i);
            }
        }
    }
    r = r.project(toProj);
    r.name = name;
    r = unionize(r);
    return r;
}



void Interpreter::runQueries() {
    cout << "Query Evaluation" << endl;
    for (auto query : dlp.queries){
        Relation r = evaluatePredicate(query);
        cout << query.toString() << "?";
        if (r.getTuples().size())
            cout << " Yes(" <<r.getTuples().size() << ")\n";
        else cout << " No" << endl;
        cout << r.toString();
    }
}

Relation Interpreter::evaluatePredicate(Predicate p) {
    map<string, int> variables;
    Predicate query = p;
    vector<string> toRename;
    vector<int> toProj;
    Relation r = db.relationDict.at(p.name);

    for (size_t index = 0; index < query.parameters.size(); index++){//const Parameter& param : query.parameters) {
        Parameter param = query.parameters.at(index);
        //if const r.select1(i, param);
        if (param.isString)
            r = r.select1(index, param.value);
        //else if in map, r.select2(i, i)
        else if(variables.count(param.value))
            r = r.select2(index, variables.at(param.value));
        //if map.find == map.end //key passed in is not in map  map.add(param.(i))
        else{
            variables.insert({param.value, index});
            toProj.push_back(index);
            toRename.push_back(param.value);

        }
        //else if in map select.2(i, index where we originally put the value)


    }
    //get all indexes from vector of variables
    //project( ^^^)
    r = r.project(toProj);
    //rename (list)->
    r.rename(toRename);

    return r;
}
vector<string> Interpreter::paramToString(int i) {

    vector<string> out;
    for (const Parameter& param : dlp.schemes.at(i).parameters){
        out.push_back(param.value);
    }
    return out;

}

void Interpreter::toString(Relation r) {
    cout << r.getName() << "(" << endl;
}

Relation Interpreter::unionize(Relation r) {
    auto it = db.relationDict.find(r.name);
    if (it != db.relationDict.end())
        if (db.relationDict.at(r.name).unionize(r))
            tuplesAdded = true;
    return r;
}

Graph Interpreter::makeGraph(const vector<Rule> &rules) {
    Graph graph(rules.size());
    // add code to add edges to the graph for the rule dependencies
    for (unsigned fromID = 0; fromID < rules.size(); fromID++) {
        Rule fromRule = rules.at(fromID);
        //cout << "from rule R" << fromID << ": " << fromRule.toString() << endl;
        for (unsigned pred = 0; pred < fromRule.size(); pred++) {
            Predicate bodyPred = fromRule.getBodyPredicate(pred);
            //cout << "from body predicate: " << bodyPred.toString() << endl;
            for (unsigned toID = 0; toID < rules.size(); toID++) {
                Rule toRule = rules.at(toID);
               // cout << "to rule R" << toID << ": " << toRule.toString() << endl;

                if(bodyPred.toString() == toRule.getHeadPredicate().toString()){
                    //cout << "dependency found: (R" << fromID << ",R" << toID << ")" << endl;
                    graph.addEdge(fromID, toID);
                }
            }
        }
    }
    return graph;
}
