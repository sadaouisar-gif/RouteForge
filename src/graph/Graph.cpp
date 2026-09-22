#include "Graph.h"
#include <iostream>
#include <stdexcept>

Graph::Graph(int vertices) {
    this->vertices = vertices;
    adjacencyList.resize(vertices);
}

void Graph::addEdge(int source, int destination, int weight) {
    if (source < 0 || source >= vertices ||
        destination < 0 || destination >= vertices) {
        return;
    }

    adjacencyList[source].push_back({destination, weight});
    adjacencyList[destination].push_back({source, weight});
}

void Graph::print() const {
    for (int vertex = 0; vertex < vertices; vertex++) {
        std::cout << vertex << " -> ";

        for (const auto& edge : adjacencyList[vertex]) {
            std::cout << "(" << edge.first << ", " << edge.second << ") ";
        }

        std::cout << '\n';
    }
}

int Graph::getVertexCount() const {
    return vertices;
}
const std::vector<std::pair<int, int>>& Graph::getNeighbors(int vertex) const {
    if (vertex < 0 || vertex >= vertices) {
        throw std::out_of_range("Invalid vertex");
    }

    return adjacencyList[vertex];
}