#ifndef DIRECTEDGRAPH_H_
#define DIRECTEDGRAPH_H_

#include "graph.h"

namespace ZP {

struct DirectedGraph : public Graph {

    DirectedGraph();
    DirectedGraph(DirectedGraph& graph);

    void add_edge(int src, int dst) override;
    void remove_edge(int src, int dst) override;

    bool has_cycle() override;
    bool has_cycle_dfs(int node, std::unordered_map<int, bool>& visited, std::unordered_map<int, bool>& stack);

};

}

#endif