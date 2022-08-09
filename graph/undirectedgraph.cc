#include "undirectedgraph.h"

namespace ZP {

UndirectedGraph::UndirectedGraph()
: Graph() {}

UndirectedGraph::UndirectedGraph(UndirectedGraph& graph)
: Graph(graph.edges, graph.node_set, graph.adj_list) {}

void UndirectedGraph::add_edge(int src, int dst) {
    if (adj_list[src].find(dst) == adj_list[src].end()) {
        edges++;
        adj_list[src].insert(dst);
        adj_list[dst].insert(src);
        node_set.insert(src);
        node_set.insert(dst);
    }
}

void UndirectedGraph::remove_edge(int src, int dst) {
    if (adj_list[src].find(dst) != adj_list[src].end()) {
        adj_list[src].erase(dst);
        adj_list[dst].erase(src);
        edges--;
        if (adj_list[src].size() == 0) {
            node_set.erase(src);
        }
        if (adj_list[dst].size() == 0) {
            node_set.erase(dst);
        }
    }
}

bool UndirectedGraph::has_cycle_dfs(int node, int parent, std::unordered_map<int, bool>& visited) {
    if (visited[node] == true) {
        return true;
    }
    visited[node] = true;
    for (int dst : adj_list[node]) {
        if (dst != parent && has_cycle_dfs(dst, node, visited)) {
            return true;
        }
    }
    return false;
}

bool UndirectedGraph::has_cycle() {
    std::unordered_map<int, bool> visited;
    for (auto& kv : adj_list) {
        if (visited[kv.first] == false && has_cycle_dfs(kv.first, -1, visited)) {
            return true;
        }
    }
    return false;
}

}