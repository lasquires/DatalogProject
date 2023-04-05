#pragma once
#include "Predicate.h"

class Rule {
public:
    Predicate headPredicate;
    vector<Predicate> predicates;
    string toString();
    //lab5 code:
    void addBodyPredicate(Predicate predicate){
        predicates.push_back(predicate);
    }
    Rule(Predicate headPredicate): headPredicate(headPredicate), predicates(vector<Predicate>()){}
    Predicate getBodyPredicate(unsigned int i){
        return predicates.at(i);
    }
    Predicate getHeadPredicate(){
        return headPredicate;
    }
    Rule();//lab 5 did this...If I delete it will break :'(
    unsigned int size(){
        return predicates.size();
    }
};
