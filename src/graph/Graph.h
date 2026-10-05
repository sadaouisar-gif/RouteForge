#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>

struct Position {
    double x;
    double y;
};

class Graph {
private:
    int vertices;

    std::vector<std::vector<std::pair<int, int>>> adjacencyList;

    std::vector<Position> positions;

public:
    Graph(int vertices);

    void addEdge(int source, int destination, int weight);

    void print() const;

    int getVertexCount() const;

    const std::vector<std::pair<int, int>>&
    getNeighbors(int vertex) const;

    void setPosition(int vertex, double x, double y);

    Position getPosition(int vertex) const;
};

#endif