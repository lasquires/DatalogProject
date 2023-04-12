//
// Created by lukes on 3/13/2023.
//

#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram dl) {
    dlp = dl;
    populateDatabase();
    //TODO move this to evaluateRules()
    ruleNames = dlp.rules;
    Graph g = makeGraph(dlp.rules, false);//make reverse graph = false
    cout << "Dependency Graph\n" << g.toString() << endl;
    Graph reverse_g = makeGraph(dlp.rules, true);//make reverse graph = true
    //cout << "reverse Dependency\n" << reverse_g.toString() << endl;
    vector<int> postOrder = reverse_g.DFSForest(); //populates reverse_g postOrder
    //reverse_g postOrder
    //cout << "postOrder: " << endl;
//    int i = 0;
//    for (int node : postOrder) {
//        cout << "R" << i << ": " << node << endl;
//        i++;
//    }
//    cout << endl;

    vector<vector<int>> SCCs = g.DFSForestv2(reverse_g.postOrder);//gives SCCs

    //take SCCs loop over with rule evaluation

    //change rule evaluation to reevaluate any SCC that changed since last loop
    cout << "Rule Evaluation" << endl;
    //runRules();
    for (unsigned int i = 0; i < SCCs.size(); i++){//auto SCC : SCCs){
        vector<int> SCC = SCCs.at(i);
        sort(SCC.begin(), SCC.end());//changed reverse to sort
        cout << "SCC: ";
        stringstream components;
        for (auto& component : SCC) {
            components << "R" << component;
            if (component != SCC.at(SCC.size()-1))
                components << ",";
        }
        cout << components.str() << endl;

        //print out which rules it's running
        //this goes inside of runrules
        passes = 0;
        runRules(SCC, g);
        //passes = 0;
//        if (SCC.size() == 1 && g.getNode(SCC.at(0)).adjacentNodeIDs.size() == 0) {//if there is only one node and it doesn't have adjacent nodes
//            passes++;
//            cout << ruleNames.at(SCC.at(0)).toString() << endl;
//            evaluateRule(ruleNames.at(SCC.at(0)));
//        }
//        else
//            runRules(SCC, g);
        cout << passes << " passes: " << components.str() << endl;
    }



        //bool hasAdjacentNodes = true;
        //int passes = 0;
        //runRules(SCC);
        //while changes in scc loop  loops++
        //while(hasAdjacentNodes) {
           // passes++;

//            for (auto rule: SCC) {
//                if (passes == 1)
//                    cout << "SCC: R" << rule << endl;
//                cout << ruleNames.at(rule).toString() << endl;
//                evaluateRule(ruleNames.at(rule));
//                hasAdjacentNodes = false;
//                if(!hasAdjacentNodes)
//                    cout << passes << " passes: R" << rule << endl;
//            }
       // }

    //TODO end rule evaluation here
    //cout << "\nScheme   s populated after " << passes << " passes through the Rules.\n" << endl;
    cout << endl;
    runQueries();
}

void Interpreter::runRules(vector<int> SCC, Graph g) {//runs rules inside of an SCC
    //proj 5 optimizing runRules()
    //Build dependency graph
//        Assign a numeric identifier to each rule starting with zero.
//        Assign the identifiers to the rules in the order the rules appear in
//        the input. Use 0 for the first rule, 1 for the second rule, etc.

//    for (int i = 0; i < dlp.rules.size(); i++)
//        ruleNames.push_back(dlp.rules.at(i));//oh wait this is just dlp.rules
        //ruleNames[i] = dlp.rules.at(i);

//        Make a node in the graph for each rule identifier. Don't add the same node
//        more than once

    //Graph g = Graph(dlp.rules.size());
//    Make an edge in the graph for each rule dependency. Add an edge to the graph from
//    node x to node y if the evaluation of x depends on the result of y. Rule A depends
//    on rule B if any of the predicate names in the body of rule A is the same as the
//    predicate name of the head of rule B. Don't add the same edge to the graph more than once.

    //for nodeX in g.nodes:
        //for nodeY in g.nodes



    //for rule_dependency in rule_dependencies:
        //if depends_on(nodeX, nodeY): ////key of nodeX in graph == key of ruleA in ruleNames  (same for Y and B)
            //g[i]      nodeX.addEdge(nodeY)

                                                    //def depends_on(Rule A, Rule B):
                                                        //depends_on = false
                                                        //if pred_name in A.body == pred_name in B.head
                                                            //depends_on = true;
                                                        //return depends_on;
    //build reverse dependency graph
    //run DFS-forest on reverse dependency
    //find_SCCs
    //evaluate rules in each component of SCC
    passes++;
    bool noSelfLoop = true;
    for (auto ajNode : g.getNode(SCC.at(0)).adjacentNodeIDs){
        if (ajNode == SCC.at(0))
            noSelfLoop = false;
    }
    if (SCC.size() == 1 && noSelfLoop){//g.getNode(SCC.at(0)).adjacentNodeIDs.size() == 0) {//if there is only one node and it doesn't have adjacent nodes
        //passes++;
        //it can have adjacent nodes that aren't itself -> check
        cout << ruleNames.at(SCC.at(0)).toString() << endl;
        evaluateRule(ruleNames.at(SCC.at(0)));
        return;
    }
    else {
        //runRules(SCC, g);
        //cout << passes << " passes: " << components.str() << endl;
        //passes += 1;
        tuplesAdded = false;
        for (auto rule: SCC) {
            //for (auto rule : dlp.rules) {
            Rule ru = ruleNames.at(rule);
            cout << ru.toString() << endl;
            Relation r = db.relationDict.at(ru.headPredicate.name);
            evaluateRule(ru);
//            if (rules.size() == 1)//&& ruleNames.at(rules.))
//                return;
        }
    }
    if (tuplesAdded) {
        runRules(SCC, g);
        //passes++;
    }
    else
        return;//cout << passes << " passes: R" << endl;//rule << endl;
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

Graph Interpreter::makeGraph(const vector<Rule> &rules, bool reverse = false) {
    //cout << "in makeGraph(): making graph" << endl;
    Graph graph(rules.size());
    for (unsigned fromID = 0; fromID < rules.size(); fromID++) {
        Rule fromRule = rules.at(fromID);
        for (unsigned pred = 0; pred < fromRule.size(); pred++) {
            Predicate bodyPred = fromRule.getBodyPredicate(pred);
            for (unsigned toID = 0; toID < rules.size(); toID++) {
                Rule toRule = rules.at(toID);

                if(bodyPred.name == toRule.headPredicate.name){//getHeadPredicate.toString()){
                    if (reverse)
                        graph.addEdge(toID, fromID); //creates reverse dependency graph
                    else
                        graph.addEdge(fromID, toID);
                }
            }
        }
    }
    //cout << "returning graph" << endl;
    return graph;
}

