#include "DFS.h"
#include <stdexcept>

void dfsHelper(
    const Graph& graph,
    int currentVertex,
    std::vector<bool>& visited,
    std::vector<int>& traversalOrder
) {
    visited[currentVertex] = true;
    traversalOrder.push_back(currentVertex);

    for (const auto& edge : graph.getNeighbors(currentVertex)) {
        int neighbor = edge.first;

        if (!visited[neighbor]) {
            dfsHelper(graph, neighbor, visited, traversalOrder);
        }
    }
}

std::vector<int> dfs(const Graph& graph, int startVertex) {
    if (startVertex < 0 || startVertex >= graph.getVertexCount()) {
        throw std::out_of_range("Invalid start vertex");
    }

    std::vector<bool> visited(graph.getVertexCount(), false);
    std::vector<int> traversalOrder;

    dfsHelper(graph, startVertex, visited, traversalOrder);

    return traversalOrder;
}