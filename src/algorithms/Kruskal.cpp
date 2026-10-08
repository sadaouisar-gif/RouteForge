#include "Kruskal.h"
#include "../structures/DisjointSet.h"

#include <vector>
#include <algorithm>
#include <stdexcept>

KruskalResult kruskal(const Graph& graph) {

    if (graph.isDirected()) {
        throw std::invalid_argument(
            "Kruskal requires an undirected graph"
        );
    }

    int vertexCount = graph.getVertexCount();

    std::vector<MSTEdge> allEdges;

    // Extract all unique edges from the graph.
    for (int source = 0;
         source < vertexCount;
         source++) {

        for (const auto& edge :
             graph.getNeighbors(source)) {

            int destination = edge.first;
            int weight = edge.second;

            // Because the graph is undirected,
            // every edge exists twice.
            if (source < destination) {

                allEdges.push_back({
                    source,
                    destination,
                    weight
                });
            }
        }
    }

    // Sort edges by increasing weight.
    std::sort(
        allEdges.begin(),
        allEdges.end(),
        [](const MSTEdge& edgeA,
           const MSTEdge& edgeB) {

            return edgeA.weight < edgeB.weight;
        }
    );

    DisjointSet disjointSet(vertexCount);

    std::vector<MSTEdge> mstEdges;

    int totalWeight = 0;

    for (const MSTEdge& edge : allEdges) {

        if (disjointSet.unite(
                edge.source,
                edge.destination)) {

            mstEdges.push_back(edge);

            totalWeight += edge.weight;

            if (mstEdges.size() ==
                static_cast<size_t>(
                    vertexCount - 1
                )) {

                break;
            }
        }
    }

    bool connected =
        mstEdges.size() ==
        static_cast<size_t>(
            vertexCount - 1
        );

    return {
        mstEdges,
        totalWeight,
        connected
    };
}