//
// Created by lukes on 1/22/2023.
//

#include "Scanner.h"
#include "Token.h"

char Scanner::GetCurrChar() {
    char currChar = input[index];
    return currChar;
}

char Scanner::GetNextChar() {
    char currChar = input[index];
    index++;
    return currChar;
}


char Scanner::PeekNextChar() {
    if (input[index] == '\0'){
        return '\0';
    }
    return input[index];
}
int Scanner::setNumTokens() {
    numTokens++;
    return 0;
}

int Scanner::getNumTokens() {
    return numTokens;
}
void Scanner::setTokens() {
    vector<Token> tokens;
    Token t = GetNextToken();
    if (t.getType() != END_LINE && t.getType() != COMMENT) tokens.push_back(t);
    while (GetCurrChar()!= '\0'){
        t = Token(GetNextToken());
        if (t.getType() != END_LINE && t.getType() != COMMENT) tokens.push_back(t);
    }
    tokens.emplace_back(_EOF, "", line);
    tokenList = tokens;
    //return tokens;
};

Token Scanner::GetNextToken() {
    char currChar = GetNextChar();
    if (currChar == '\n'){
        //currChar = GetNextChar();
        setNumLines();
        return {END_LINE,"", line};
    }
    while (isspace(currChar)/* || currChar == '\n'*/){
        currChar = GetNextChar();
        if (currChar == '\n'){
            //currChar = GetNextChar();
            setNumLines();
            return {END_LINE,"", line};
        }
       // if (input.size() == '\n' || isspace(input.size())) exit(0);
    }
    if (currChar == ',') return {COMMA, ",", line};
    else if (currChar== '.') return {PERIOD, ".", line};
    else if (currChar== '?') return {Q_MARK, "?", line};
    else if (currChar== ';') return {SEMI_COLON, ";", line};
    else if (currChar== '=') return {EQUALS, "=", line};
    else if (currChar== '(') return {LEFT_PAREN, "(", line};
    else if (currChar== ')') return {RIGHT_PAREN, ")", line};
    else if (currChar == EOF) return {_EOF,"", line};
    else if (currChar == '\'') return GetString(currChar);
    else if (isalpha(currChar)) return GetID(currChar);
    else if (currChar == '#') return GetComment(currChar);
    else if (currChar== ':'){
        if (GetCurrChar() == '-'){
            GetNextToken();
            return {COLON_DASH, ":-", line};
        }
        return {COLON, ":", line};
    }
    else{
        stringstream  ss;
        ss << currChar;
        return {UNDEFINED, ss.str(), line};
    }
}




Token Scanner::GetString(char in) {
    bool valid_string = false;
    string outString;
    int stringLine = line;
    outString+= in;
    char currChar = GetNextChar();
    while(!valid_string) {
        if (currChar != '\'' && currChar !='\0') {
            outString += currChar;
            currChar = GetNextChar();
            if(currChar=='\n') setNumLines();
        }
        else if((PeekNextChar() == '\'')){
            //currChar = GetNextChar();
            outString += currChar;
            currChar = GetNextChar();
            currChar = GetNextChar();
        }
        else if ((PeekNextChar() != '\'') && currChar != '\0'){
            valid_string = true;
        }
        else if (currChar == '\0'){
            index--;
            return {UNDEFINED , outString, stringLine};
        }

        }
    outString += '\'';
    return {STRING, outString, stringLine};
}

Token Scanner::GetID(char in) {
    string outString;
    outString+= in;
    char currChar = GetNextChar();

    while (isalpha(currChar) || isdigit(currChar) || currChar == '\''){
        outString += currChar;
        currChar = GetNextChar();
    }
    index--;
    if (reservedWords.count(outString)) return {reservedWords[outString], outString, line};
    return {ID, outString, line};
}

Token Scanner::GetComment(char in) {
    string outString;
    outString+= in;
    char currChar = GetNextChar();
    while(currChar != '\n'){                                       //(index <= (int)input.size()){
        outString += currChar;
        currChar = GetNextChar();
    }
    //index--;
    setNumLines();
    return {COMMENT, outString, line-1};
}

string Scanner::TokensToString() {
    if(input.empty()) return "";
    stringstream TokenString;
    setTokens();
    for (const auto& tok : getTokens()){
        TokenString << "(" << tok.typeName() << ","
         << "\"" << tok.getValue() << "\"" << ","
         << tok.getLine() << ")\n";
    }
    return TokenString.str();
}

int Scanner::setNumLines() {
    line++;
    return 0;
}

int Scanner::getNumLines() {
    return line;
}

vector<Token> Scanner::getTokens() {
    return tokenList;
}


