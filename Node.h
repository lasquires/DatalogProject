#pragma once
#include <set>
#include <string>
#include <sstream>
using namespace std;
class Node {
private:




public:
    set<int> adjacentNodeIDs;

    bool visited = false;
    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
    }
    int NodeID;
    string toString();
};


