#include <iostream>
#include "Interpreter.h"
#include <iostream>
#include <sstream>
#include "Token.h"
#include "Node.h"
#include "Graph.h"
#include "Parser.h"
#include "Scanner.h"
using namespace std;
int main(int argc, char* argv[]) {
//    string input_line;
//    string scannerString;
//    int currLine = 1;
//    ifstream inFS(argv[1]);
//    //int totTokens = 0;
//    if(!inFS.is_open()){
//        std::cout << "Input file input.txt could not be opened.\n";
//        return 1;
//    }
//    //cout << argv[1] <<" opened successfully\n";
//    while (getline(inFS, input_line)){
//        scannerString += input_line;
//        scannerString += '\n';
//    }
//    //cout << scannerString << endl;
//    Scanner s = Scanner(scannerString, currLine);
//    s.TokensToString();
//    Parser p = Parser(s.getTokens());
//    DatalogProgram dl = p.parse();
//    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//    Interpreter ip = Interpreter(dl);

//Lab5
    // predicate names for fake rules
    // first is name for head predicate
    // second is names for body predicates
    pair<string,vector<string>> ruleNames[] = {
            { "A", { "B", "C" } },
            { "B", { "A", "D" } },
            { "B", { "B" } },
            { "E", { "F", "G" } },
            { "E", { "E", "F" } },
    };


    vector<Rule> rules;

    for (auto& rulePair : ruleNames) {
        string headName = rulePair.first;
        Rule rule = Rule(Predicate(headName));
        vector<string> bodyNames = rulePair.second;
        for (auto& bodyName : bodyNames)
            rule.addBodyPredicate(Predicate(bodyName));
        rules.push_back(rule);
    }

    Graph graph = Interpreter::makeGraph(rules);
    cout << graph.toString();


    return 0;
}


