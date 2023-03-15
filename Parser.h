//
// Created by lukes on 2/4/2023.
//
#pragma once
#include <string>
#include <utility>
#include "Token.h"
#include "Predicate.h"
#include "DatalogProgram.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include <vector>

#ifndef LAB1_PARSER_H
#define LAB1_PARSER_H


class Parser {
    private:
        vector<Token> tokens;
        Predicate p;
        Rule r;
        Parameter param;
        DatalogProgram d;
    public:
    Parser(const vector<Token>& tokens) : tokens(tokens){}
    TokenType tokenType() const;
    string tokenValue();
    void advanceToken();
    DatalogProgram parse();
    void match(TokenType t);

    void datalogProgram();

    void schemeList();
    void factList();
    void ruleList();
    void queryList();
    void scheme();
    void fact();
    void rule();
    void query();

    void headPredicate();
    void predicate();

    void predicateList();
    void parameterList();
    void stringList();
    void idList();
    void parameter();


};


#endif //LAB1_PARSER_H
