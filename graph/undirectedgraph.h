#ifndef UNDIRECTEDGRAPH_H_
#define UNDIRECTEDGRAPH_H_

#include "graph.h"

namespace ZP {

struct UndirectedGraph : public Graph {

    UndirectedGraph();
    UndirectedGraph(UndirectedGraph& graph);

    void add_edge(int src, int dst) override;
    void remove_edge(int src, int dst) override;

    bool has_cycle() override;
    bool has_cycle_dfs(int node, int parent, std::unordered_map<int, bool>& visited);

};

}

#endif