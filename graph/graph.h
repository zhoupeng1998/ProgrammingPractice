#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace ZP {

struct Graph {

    Graph();
    Graph(int nodes, std::unordered_set<int>& node_set, std::unordered_map<int, std::unordered_set<int>>& adj_list);

    virtual void add_edge(int src, int dst) = 0;
    virtual void remove_edge(int src, int dst) = 0;

    inline int num_nodes() { return node_set.size(); }
    inline int num_edges() { return edges; }

    void dump_graph();

    int edges;

    std::unordered_set<int> node_set;
    std::unordered_map<int, std::unordered_set<int>> adj_list;

    virtual bool has_cycle() { return false; }
    virtual std::vector<int> topological_order() { return {}; }

};

}

#endif