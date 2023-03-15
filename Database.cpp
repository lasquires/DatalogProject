#include "Database.h"

void Database::addRelation(string name, Relation relation) {
    relationDict.insert({name, relation});
}

map<string, Relation> Database::getDatabase() {
    return relationDict;
}
