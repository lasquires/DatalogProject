#include <iostream>
#include <sstream>
#include "Token.h"
#include "Parser.h"
#include "Scanner.h"
using namespace std;
int main(int argc, char* argv[]) {

//    vector<Token> tokens = {
//            Token(ID,"Ned",2),
//            Token(LEFT_PAREN,"(",2),
//            Token(ID,"Ted",2),
//            Token(COMMA,",",2),
//            //Token(ID,"Zed",2),
//            Token(RIGHT_PAREN,")",2),
//    };
//
//    Parser p = Parser(tokens);
//    p.scheme();
//    return 0;



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
    p.parse();
//    p.scheme();
//    cout << p.tokenType() << endl;
//    p.advanceToken();
//    cout << p.tokenType() << endl;
//    p.advanceToken();
//    cout << p.tokenType() << endl;
//    p.throwError();
//    Token t = Token(_EOF, "", s.getNumLines());
//    cout << t.toString();
//    totTokens = s.getNumTokens();
//    cout <<"Total Tokens = " << totTokens << endl;
    return 0;
}


