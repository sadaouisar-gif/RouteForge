#include "Prim.h"

#include <queue>
#include <vector>
#include <tuple>
#include <functional>
#include <stdexcept>

PrimResult prim(
    const Graph& graph,
    int startVertex
) {

    if (graph.isDirected()) {
        throw std::invalid_argument(
            "Prim requires an undirected graph"
        );
    }

    if (startVertex < 0 ||
        startVertex >= graph.getVertexCount()) {

        throw std::out_of_range(
            "Invalid start vertex"
        );
    }

    int vertexCount = graph.getVertexCount();

    std::vector<bool> visited(
        vertexCount,
        false
    );

    std::vector<MSTEdge> mstEdges;

    int totalWeight = 0;

    // {weight, source, destination}
    std::priority_queue<
        std::tuple<int, int, int>,
        std::vector<std::tuple<int, int, int>>,
        std::greater<std::tuple<int, int, int>>
    > priorityQueue;

    visited[startVertex] = true;

    // Add all edges leaving the start vertex
    for (const auto& edge :
         graph.getNeighbors(startVertex)) {

        int neighbor = edge.first;
        int weight = edge.second;

        priorityQueue.push({
            weight,
            startVertex,
            neighbor
        });
    }

    while (!priorityQueue.empty() &&
           mstEdges.size() <
               static_cast<size_t>(vertexCount - 1)) {

        auto [weight, source, destination] =
            priorityQueue.top();

        priorityQueue.pop();

        // Ignore edges leading to a vertex
        // already included in the MST
        if (visited[destination]) {
            continue;
        }

        visited[destination] = true;

        mstEdges.push_back({
            source,
            destination,
            weight
        });

        totalWeight += weight;

        // Add the new vertex's outgoing edges
        for (const auto& edge :
             graph.getNeighbors(destination)) {

            int neighbor = edge.first;
            int neighborWeight = edge.second;

            if (!visited[neighbor]) {

                priorityQueue.push({
                    neighborWeight,
                    destination,
                    neighbor
                });
            }
        }
    }

    bool connected =
        mstEdges.size() ==
        static_cast<size_t>(vertexCount - 1);

    return {
        mstEdges,
        totalWeight,
        connected
    };
}