
#include "Graph.h"

string Graph::toString() {
    stringstream out;
    for (auto& pair: nodes) {
        int nodeID = pair.first;
        Node node = pair.second;
        out << 'R' << nodeID << ':' << node.toString() << endl;
    }
    return out.str();
}

vector <int> Graph::DFSForest() {

    for (auto node : nodes) {
        node.second.NodeID = node.first;
        node.second.visited = false;
        nodes.at(node.first) = node.second;
    }
    for (auto& node : nodes)
        if (!node.second.visited) {
            this->dfs(node.second);
        }
    return postOrder;
//    vector<vector<int>> dfsForest;
//
//    for (int i = 0; i < nodes.size(); ++i) {
//        if (!nodes.at(i).visited) {
//            vector<int> component;
//            DFSUtil(u, visited, component);
//            dfsForest.push_back(component);
//        }
//    }
//
//    return dfsForest;
}

void Graph::dfs(Node& x) {
    x.visited = true;
    for (auto node : x.adjacentNodeIDs) {
        if (!nodes.at(node).visited) {

            dfs(nodes.at(node));
        }
    }


    postOrder.push_back(x.NodeID);
    return;
}

vector<vector<int>> Graph::DFSForestv2(vector<int> reversePostOrder) {
    //vector<int> original = reversePostOrder;
    reverse(reversePostOrder.begin(), reversePostOrder.end());
    vector<vector<int>> SCCs;
    for (auto node : nodes) {
        node.second.NodeID = node.first;
        node.second.visited = false;
        nodes.at(node.first) = node.second;
    }
//    We'll start at the last node in the post-order and do a DFS starting there////is that the first in the reverse_g postorder?
    for (int node : reversePostOrder){
        if(!nodes.at(node).visited) {
            postOrder.clear();
            dfs(nodes.at(node));
            SCCs.push_back(postOrder);
        }
    }
    return SCCs;

//    We'll visit any nodes that can be reached. These are in the same SCC.
//    We'll do another DFS for the next unvisited node in the post-order, etc.


    return SCCs;
}
