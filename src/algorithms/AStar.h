#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include "../graph/Graph.h"

struct AStarResult {
    std::vector<int> path;
    int distance;
};

AStarResult aStar(
    const Graph& graph,
    int startVertex,
    int destination
);

#endif