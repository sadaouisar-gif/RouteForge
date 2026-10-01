#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include "../graph/Graph.h"

struct DijkstraResult {
    std::vector<int> distances;
    std::vector<int> previous;
};

DijkstraResult dijkstra(const Graph& graph, int startVertex);

std::vector<int> reconstructPath(
    const DijkstraResult& result,
    int startVertex,
    int destination
);

#endif