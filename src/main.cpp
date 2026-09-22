#include "graph/Graph.h"
#include "algorithms/DFS.h"
#include "algorithms/BFS.h"
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

    std::vector<int> bfsResult = bfs(graph, 0);

    std::cout << "BFS from vertex 0: ";

    for (int vertex : bfsResult) {
        std::cout << vertex << " ";
    }

    std::cout << '\n';

    std::vector<int> dfsResult = dfs(graph, 0);

    std::cout << "DFS from vertex 0: ";

    for (int vertex : dfsResult) {
         std::cout << vertex << " ";
    }

    std::cout << '\n';

    return 0;
}