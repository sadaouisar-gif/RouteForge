#include "Graph.h"

#include <iostream>
#include <stdexcept>

Graph::Graph(int vertices, bool directed) {

    if (vertices < 0) {
        throw std::invalid_argument(
            "Number of vertices cannot be negative"
        );
    }

    this->vertices = vertices;
    this->directed = directed;

    adjacencyList.resize(vertices);
    positions.resize(vertices);
}


void Graph::addEdge(
    int source,
    int destination,
    int weight
) {

    if (source < 0 || source >= vertices ||
        destination < 0 || destination >= vertices) {

        throw std::out_of_range("Invalid vertex");
    }

    // source -> destination
    adjacencyList[source].push_back({
        destination,
        weight
    });

    // For an undirected graph, also add:
    // destination -> source
    if (!directed) {

        adjacencyList[destination].push_back({
            source,
            weight
        });
    }
}


void Graph::print() const {

    for (int vertex = 0;
         vertex < vertices;
         vertex++) {

        std::cout << vertex << " -> ";

        for (const auto& edge :
             adjacencyList[vertex]) {

            std::cout << "("
                      << edge.first
                      << ", "
                      << edge.second
                      << ") ";
        }

        std::cout << '\n';
    }
}


int Graph::getVertexCount() const {
    return vertices;
}


bool Graph::isDirected() const {
    return directed;
}


const std::vector<std::pair<int, int>>&
Graph::getNeighbors(int vertex) const {

    if (vertex < 0 || vertex >= vertices) {
        throw std::out_of_range("Invalid vertex");
    }

    return adjacencyList[vertex];
}


void Graph::setPosition(
    int vertex,
    double x,
    double y
) {

    if (vertex < 0 || vertex >= vertices) {
        throw std::out_of_range("Invalid vertex");
    }

    positions[vertex] = {x, y};
}


Position Graph::getPosition(int vertex) const {

    if (vertex < 0 || vertex >= vertices) {
        throw std::out_of_range("Invalid vertex");
    }

    return positions[vertex];
}