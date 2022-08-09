#include <iostream>

#include "graph.h"

namespace ZP {

Graph::Graph()
: edges(0) {}

Graph::Graph(int edges, std::unordered_set<int>& node_set, std::unordered_map<int, std::unordered_set<int>>& adj_list)
: edges(edges), node_set(node_set), adj_list(adj_list) {}

void Graph::dump_graph() {
    std::cout << "Nodes: " << num_nodes() << std::endl;
    std::cout << "Edges: " << num_edges() << std::endl;
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