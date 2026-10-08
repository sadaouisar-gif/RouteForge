#ifndef PRIM_H
#define PRIM_H

#include <vector>
#include "../graph/Graph.h"

struct MSTEdge {
    int source;
    int destination;
    int weight;
};

struct PrimResult {
    std::vector<MSTEdge> edges;
    int totalWeight;
    bool connected;
};

PrimResult prim(const Graph& graph, int startVertex);

#endif