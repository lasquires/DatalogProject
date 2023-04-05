
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
