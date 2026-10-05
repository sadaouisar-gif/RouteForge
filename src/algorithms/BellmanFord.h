#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <vector>
#include "../graph/Graph.h"

struct BellmanFordResult {
    std::vector<int> distances;
    std::vector<int> previous;
    bool hasNegativeCycle;
};

BellmanFordResult bellmanFord(
    const Graph& graph,
    int startVertex
);

std::vector<int> reconstructBellmanFordPath(
    const BellmanFordResult& result,
    int startVertex,
    int destination
);

#endif