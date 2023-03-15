#pragma once
#include <map>
#include "Relation.h"
class Database {
//map <string, Tuple> factPredicate;
public:
//take in name:relation
    void addRelation(string name, Relation relation);
    map<string, Relation> getDatabase();

    map <string, Relation> relationDict;
};
