#include <iostream>
#include <queue>

#include "directedgraph.h"

namespace ZP {

DirectedGraph::DirectedGraph()
: Graph() {}

DirectedGraph::DirectedGraph(DirectedGraph& graph)
: Graph(graph.edges, graph.node_set, graph.adj_list), incoming_count(graph.incoming_count) {}

void DirectedGraph::add_edge(int src, int dst) {
    if (adj_list[src].find(dst) == adj_list[src].end()) {
        edges++;
        adj_list[src].insert(dst);
        node_set.insert(src);
        node_set.insert(dst);
        incoming_count[dst]++;
    }
}

void DirectedGraph::remove_edge(int src, int dst) {
    if (adj_list[src].find(dst) != adj_list[src].end()) {
        adj_list[src].erase(dst);
        edges--;
        incoming_count[dst]--;
        if (incoming_count[src] == 0 && adj_list[src].size() == 0) {
            node_set.erase(src);
        }
        if (incoming_count[dst] == 0 && adj_list[dst].size() == 0) {
            node_set.erase(dst);
        }
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

std::vector<int> DirectedGraph::topological_order() {
    std::queue<int> que;
    std::vector<int> result;
    for (auto& kv : adj_list) {
        if (incoming_count[kv.first] == 0) {
            que.push(kv.first);
        }
    }
    while (que.size() > 0) {
        int node = que.front();
        que.pop();
        result.push_back(node);
        for (int dst : adj_list[node]) {
            incoming_count[dst]--;
            if (incoming_count[dst] == 0) {
                que.push(dst);
            }
        }
    }
    if (result.size() != num_nodes()) {
        return {};
    }
    return result;
}


}