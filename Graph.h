#pragma once
#include "Node.h"
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
class Graph {

private:

    map<int,Node> nodes;

public:

    Graph(int size) {
        for (int nodeID = 0; nodeID < size; nodeID++)
            nodes[nodeID] = Node();
    }

    Node getNode(int nodeID){
        return nodes[nodeID];
    }
    void addEdge(int fromNodeID, int toNodeID) {
        nodes[fromNodeID].addEdge(toNodeID);
    }

    string toString();
    void dfs(Node& x);
    vector<int> DFSForest();
    vector<vector<int>> DFSForestv2(vector<int> reversePostOrder);

    vector<int> postOrder;
};
