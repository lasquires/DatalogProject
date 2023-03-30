#include "Database.h"

void Database::addRelation(string name, Relation relation) {
    relationDict.insert({name, relation});
}

map<string, Relation> Database::getDatabase() {
    return relationDict;
}

int Database::getDatabaseSize() {
    int size = 0;
    for (auto relation : relationDict)
        for (auto tuple : relation.second.getTuples())
            size ++;
    return size;
}
