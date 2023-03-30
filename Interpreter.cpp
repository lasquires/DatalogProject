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

    //int dbsize = db.getDatabaseSize();
    passes += 1;
    tuplesAdded = false;
    for (auto rule : dlp.rules) {
        cout << rule.toString() << endl;
        Relation r = db.relationDict.at(rule.headPredicate.name);

        //unsigned int tuplesSize = r.getTuples().size();
        evaluateRule(rule);
//        if (r.getTuples().size() != tuplesSize)
//            cout << r.toString();
        //tuplesAdded = false;
//        Relation r = evaluatePredicate(rule.predicates.at(0));
//        //r.rename(rule.headPredicate.name)
//        for (int i = 1; i < rule.predicates.size(); i++) {//auto predicate : rule.predicates){
//            r = r.join(evaluatePredicate(rule.predicates.at(i)));
//        }
//        vector<int> toProj;
//        for (auto param: rule.headPredicate.parameters) {
//            for (int i = 0; i < r.scheme.names.size(); i++) {
//                if (param.value == r.scheme.names.at(i)) {
//                    toProj.push_back(i);
//                }
//            }
//        }
//        r = r.project(toProj);
//        string newName;
//        for (auto cols: r.scheme.names)  newName+=cols;
//        r.name = newName;
//        cout << "name of this relation: " << r.getName() << endl;
//        db.addRelation(r.getName(), r);
//        cout << "R.tostring(): \n" << r.toString() << endl;
    }
    if (tuplesAdded)
        runRules();

    //if(dbsize != db.getDatabaseSize()) runRules();
}
Relation Interpreter::evaluateRule(Rule rule) {
    //cout << rule.toString() << endl;
    Relation r = evaluatePredicate(rule.predicates.at(0));
    r.name = rule.headPredicate.name;
    string name = r.name;
    //r.rename(rule.headPredicate.name)
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
//    string newName;
//    for (auto cols: r.name)  newName+=cols;
    r.name = name;
    //cout << "name of this relation: " << r.getName() << endl;

    r = unionize(r);
//    if (tuplesAdded) runRules();
    //db.addRelation(r.getName(), r);
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
    //cout << "in evaluatePredicate()" << endl;

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
//        for (auto tuple : r.getTuples()) {
//            db.relationDict.at(r.name).addTuple(tuple);
//            //tuplesAdded = true;
//        }
//    //Scheme s = it->second.scheme;
//    r.scheme = it->second.scheme;
//    //Scheme ss = r.scheme;
    return r;
}



//    while(true){
//        if (dlp.schemes)
//
//
//    }
//    }
//    if (//for scheme in schemes) send each scheme to relation ->name
//    if (//for fact in facts) send each  to tuple, send set tuple to relation.




//
//    db =
//}
//questions, what should database maps be made of