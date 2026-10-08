#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>
#include "../graph/Graph.h"
#include "Prim.h"

struct KruskalResult {
    std::vector<MSTEdge> edges;
    int totalWeight;
    bool connected;
};

KruskalResult kruskal(const Graph& graph);

#endif