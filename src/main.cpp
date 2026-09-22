#include "graph/Graph.h"
#include <iostream>

int main() {
    Graph graph(5);

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 4, 3);

    graph.print();

    std::cout << "Number of vertices: "
          << graph.getVertexCount()
          << '\n';

    return 0;
}
