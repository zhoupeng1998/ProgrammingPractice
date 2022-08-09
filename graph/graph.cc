#include <iostream>

#include "graph.h"

namespace ZP {

Graph::Graph()
: nodes(0), edges(0) {}

Graph::Graph(int nodes, int edges, std::unordered_map<int, std::unordered_set<int>>& adj_list)
: nodes(nodes), edges(edges), adj_list(adj_list) {}

void Graph::dump_graph() {
    std::cout << "Nodes: " << nodes << std::endl;
    std::cout << "Edges: " << edges << std::endl;
    for (auto& pair : adj_list) {
        if (pair.second.size() != 0) {
            std::cout << pair.first << ": [ ";
            for (int num : pair.second) {
                std::cout << num << " ";
            }
            std::cout << "]" << std::endl;
        }
    }
}

}