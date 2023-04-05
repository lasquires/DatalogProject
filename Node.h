#pragma once
#include <set>
#include <string>
#include <sstream>
using namespace std;
class Node {
private:

    set<int> adjacentNodeIDs;

public:

    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
    }
    string toString();
};


