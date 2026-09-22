#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>

class Graph {
private:
    int vertices;
    std::vector<std::vector<std::pair<int, int>>> adjacencyList;

public:
    Graph(int vertices);

    void addEdge(int source, int destination, int weight);

    void print() const;
    int getVertexCount() const;

    const std::vector<std::pair<int, int>>& getNeighbors(int vertex) const;
};

#endif