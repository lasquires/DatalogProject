#pragma once

#include <string>
#include <utility>
#include "Token.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include <vector>

using namespace std;

class Scanner {
private:
    string input;
    int line;
    int index;
    int numTokens = 0;
    vector<Token> tokenList;

    map<string, TokenType> reservedWords = {
            {"Schemes", SCHEMES},
            {"Rules", RULES},
            {"Queries", QUERIES},
            {"Facts", FACTS}
    };

public:
    Scanner(string input, int line) : input(input), line(line), index(0) {}
    vector<Token> getTokens();
    void setTokens();
//    Token scanToken();
    Token GetNextToken();
    char GetCurrChar();
    char GetNextChar();
    char PeekNextChar();
    int setNumLines();
    int getNumLines();
    int setNumTokens();
    int getNumTokens();
    char goNextChar();
    Token GetString(char in);
    Token GetID(char in);
    Token GetComment(char in);
    string TokensToString();
    int getTotalTokens();

};




//https://faculty.cs.byu.edu/~barker/cs236/labs/lab1-session.html