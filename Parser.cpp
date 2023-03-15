//

#include "Parser.h"



TokenType Parser::tokenType() const {
    return tokens.at(0).getType();
}
string Parser::tokenValue() {
    return tokens.at(0).getValue();
}


void Parser::advanceToken() {
    tokens.erase(tokens.begin());
}

DatalogProgram Parser::parse() {
    datalogProgram();
    return d;
}

void Parser::match(TokenType t) {
    //cout << "match: " << t << endl;
    if (t == tokenType()) advanceToken();
    else throw tokens.at(0);
}
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void Parser::datalogProgram(){
    try{
        match(SCHEMES);
        match(COLON);
        scheme();
        schemeList();
        if (d.schemes.empty()) throw tokens.at(0);
        match(FACTS);
        match(COLON);
        factList();
        match(RULES);
        match(COLON);
        ruleList();
        match(QUERIES);
        match(COLON);
        query();
        queryList();
        match(_EOF);

    }catch (Token badToken) {
        cout << "Failure!\n  " << "(" << badToken.typeName() << ","<< "\"" << badToken.getValue() << "\"" << ","<< badToken.getLine() << ")\n";
        return;
    }
    //cout << d.toString();
    return;// d;
}
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void Parser::schemeList() {
    if (tokenType() == ID) {

        scheme();
        schemeList();
    } else {
        // lambda
    }
}
void Parser::factList() {
    if (tokenType() == ID) {
        fact();
        factList();
    } else {
        // lambda
    }
}
void Parser::ruleList() {
    if (tokenType() == ID) {
        rule();
        ruleList();
    } else {
        // lambda
    }
}
void Parser::queryList() {
    if (tokenType() == ID) {
        query();
        queryList();
    } else {
        // lambda
    }
}
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void Parser::scheme() {
    if (tokenType() == ID){
        p.name = tokenValue();
        p.parameters.clear();
        match(ID);
        match(LEFT_PAREN);
        param.value = tokenValue();
        p.parameters.push_back(param);
        match(ID);
        idList();
        match(RIGHT_PAREN);
        d.schemes.push_back(p);
    }

}
void Parser::fact() {
    if (tokenType() == ID){
        p.name = tokenValue();
        p.parameters.clear();
        match(ID);
        match(LEFT_PAREN);
        param.value = tokenValue();
        //param.isConstant = true;
        p.parameters.push_back(param);
        d.domain.insert(param.toString());
        //param.isConstant = false;
        match(STRING);
        stringList();
        match(RIGHT_PAREN);
        match(PERIOD);
        d.facts.push_back(p);
    }
}
void Parser::rule() {
    headPredicate();
    match(COLON_DASH);
    predicate();
    r.predicates.clear();
    r.predicates.push_back(p);
    predicateList();
    match(PERIOD);
    d.rules.push_back(r);
}
void Parser::query() {
    predicate();
    match(Q_MARK);
    d.queries.push_back(p);
}
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

void Parser::headPredicate() {
    p.name = tokenValue();
    p.parameters.clear();
    match(ID);
    match(LEFT_PAREN);
    param.value = tokenValue();
    p.parameters.push_back(param);
    match(ID);
    idList();
    r.headPredicate = p;
    match(RIGHT_PAREN);
}
void Parser::predicate() {
    p.name = tokenValue();
    p.parameters.clear();
    match(ID);
    match(LEFT_PAREN);
    parameter();
    parameterList();
    match(RIGHT_PAREN);
}
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

void Parser::predicateList() {
    if (tokenType() == COMMA) {
        match(COMMA);
        predicate();
        r.predicates.push_back(p);
        predicateList();
    } else {
        // lambda
    }
}
void Parser::parameterList() {
    if (tokenType() == COMMA) {
        match(COMMA);
        parameter();
        parameterList();
    } else {
        // lambda
    }
}
void Parser::stringList() {
    if (tokenType() == COMMA) {
        match(COMMA);
        param.value = tokenValue();
        p.parameters.push_back(param);
        d.domain.insert(param.toString());
        match(STRING);
        stringList();
    } else {
        // lambda
    }
}
void Parser::idList() {
    if (tokenType() == COMMA) {
        match(COMMA);
        param.value = tokenValue();
        p.parameters.push_back(param);
        match(ID);
        idList();
    } else {
        // lambda
    }
}

void Parser::parameter() {
    if (tokenType() == STRING){
        param.value = tokenValue();
        param.isString = true;
        p.parameters.push_back(param);
        param.isString = false;
        match(STRING);
    }
    if (tokenType() == ID) {
        param.value = tokenValue();
        p.parameters.push_back(param);
        match(ID);
    }
}








