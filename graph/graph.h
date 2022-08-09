#ifndef GRAPH_H_
#define GRAPH_H_

#include <unordered_map>
#include <unordered_set>

namespace ZP {

struct Graph {

    Graph();
    Graph(int nodes, int edges, std::unordered_map<int, std::unordered_set<int>>& adj_list);

    virtual void add_edge(int src, int dst) = 0;
    virtual void remove_edge(int src, int dst) = 0;

    inline int num_nodes() { return nodes; }
    inline int num_edges() { return edges; }

    void dump_graph();

    int nodes;
    int edges;

    std::unordered_map<int, std::unordered_set<int>> adj_list;

    virtual bool has_cycle() { return false; }

};

}

#endif