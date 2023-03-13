#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <utility>
using namespace std;

enum TokenType {
    COMMA,                    //0
    PERIOD,                     //1
    Q_MARK,                     //2
    SEMI_COLON,                    //3
    COLON,                    //4
    COLON_DASH,                    //5
    EQUALS,                    //6
    LEFT_PAREN,                    //7
    RIGHT_PAREN,                    //8
    END_LINE,                    //9
    STRING,                    //10
    ID,                    //11
    COMMENT,                    //12
    _EOF,                    //13
    SCHEMES,                    //14
    QUERIES,                    //15
    RULES,                    //16
    FACTS,                    //17
    UNDEFINED                    //18
};
class Token
{
private:
    TokenType type;
    string value;
    int line = 0;


public:
    Token(TokenType type, string value, int line) : type(type), value(value), line(line){};
    string toString();
    TokenType getType() const;
    int getLine() const;
    string getValue() const;
    string typeName() const;
};
