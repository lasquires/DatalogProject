#include <iostream>
#include "Interpreter.h"
#include <iostream>
#include <sstream>
#include "Token.h"
#include "Parser.h"
#include "Scanner.h"
using namespace std;
int main(int argc, char* argv[]) {
    string input_line;
    string scannerString;
    int currLine = 1;
    ifstream inFS(argv[1]);
    //int totTokens = 0;
    if(!inFS.is_open()){
        std::cout << "Input file input.txt could not be opened.\n";
        return 1;
    }
    //cout << argv[1] <<" opened successfully\n";
    while (getline(inFS, input_line)){
        scannerString += input_line;
        scannerString += '\n';
    }
    //cout << scannerString << endl;
    Scanner s = Scanner(scannerString, currLine);
    s.TokensToString();
    Parser p = Parser(s.getTokens());
    DatalogProgram dl = p.parse();
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    Interpreter ip = Interpreter(dl);


//    Relation studentRelation("students", Scheme( {"ID", "Name", "Major"} ));
//
//    vector<string> studentValues[] = {
//            {"'42'", "'Ann'", "'CS'"},
//            {"'64'", "'Ned'", "'EE'"},
//    };
//
//    for (auto& value : studentValues)
//        studentRelation.addTuple(Tuple(value));
//    Relation courseRelation("courses", Scheme( {"ID", "Course"} ));
//
//    vector<string> courseValues[] = {
//            {"'42'", "'CS 100'"},
//            {"'32'", "'CS 232'"},
//    };
//
//    for (auto& value : courseValues)
//        courseRelation.addTuple(Tuple(value));
//
//    studentRelation.join(courseRelation);
//    //studentRelation.join(studentRelation);


    return 0;
}


