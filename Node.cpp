//
// Created by lukes on 4/4/2023.
//

#include "Node.h"

string Node::toString() {
    stringstream outString;
    bool firstItem = true;
    for (auto& nodeID : adjacentNodeIDs) {
        if (firstItem) firstItem = false;
        else outString << ",";
        outString << 'R' << nodeID;
    }
    return outString.str();
}
