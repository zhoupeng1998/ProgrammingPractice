#include <iostream>

#include "directedgraph.h"

namespace ZP {

DirectedGraph::DirectedGraph()
: Graph() {}

DirectedGraph::DirectedGraph(DirectedGraph& graph)
: Graph(graph.nodes, graph.edges, graph.adj_list) {}

void DirectedGraph::add_edge(int src, int dst) {
    if (adj_list.find(src) == adj_list.end() || adj_list[src].size() == 0) {
        nodes++;
    }
    if (adj_list.find(dst) == adj_list.end() || adj_list[dst].size() == 0) {
        nodes++;
    }
    if (adj_list[src].find(dst) == adj_list[src].end()) {
        edges++;
        adj_list[src].insert(dst);
    }
}

void DirectedGraph::remove_edge(int src, int dst) {
    if (adj_list[src].find(dst) != adj_list[src].end()) {
        adj_list[src].erase(dst);
        edges--;
    }
    if (adj_list[src].size() == 0) {
        nodes--;
    }
    if (adj_list[dst].size() == 0) {
        nodes--;
    }
}

bool DirectedGraph::has_cycle_dfs(int node, std::unordered_map<int, bool>& visited, std::unordered_map<int, bool>& stack) {
    if (stack[node] == true) {
        return true;
    }
    if (visited[node] == true) {
        return false;
    }
    visited[node] = true;
    stack[node] = true;
    for (auto& dst : adj_list[node]) {

        if (has_cycle_dfs(dst, visited, stack)) {
            return true;
        }
    }
    stack[node] = false;
    return false;
}

bool DirectedGraph::has_cycle() {
    std::unordered_map<int, bool> visited;
    std::unordered_map<int, bool> stack;
    for (auto& kv : adj_list) {
        if (visited[kv.first] == false && has_cycle_dfs(kv.first, visited, stack)) {
            return true;
        }
    }
    return false;
}

}