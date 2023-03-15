//
// Created by lukes on 3/13/2023.
//

#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram dl) {
    dlp = dl;
    populateDatabase();
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

void Interpreter::runQueries() {

    for (auto /* const Predicate&*/ query : dlp.queries){
        Relation r = evaluateQuery(query);
        cout << query.toString() << "?";
        if (r.getTuples().size())
            cout << " Yes(" <<r.getTuples().size() << ")\n";
        else cout << " No" << endl;
        cout << r.toString();
    }
}

Relation Interpreter::evaluateQuery(Predicate p) {
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
    r.project(toProj);
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