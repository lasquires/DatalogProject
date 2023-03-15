#pragma once
#include "DatalogProgram.h"
#include "Database.h"
//#include "Predicate.h"
class Interpreter {
private:
    DatalogProgram dlp;
    Database db;
public:
    Interpreter() = default;
    explicit Interpreter(DatalogProgram dl);
    void populateDatabase();
    vector<string> paramToString(int i);
    //add queries
    void runQueries();
    Relation evaluateQuery(Predicate p);
    static void toString(Relation r);
    //string tostring();




};
