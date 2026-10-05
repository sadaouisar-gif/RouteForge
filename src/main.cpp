#include <iostream>
#include <vector>

#include "graph/Graph.h"
#include "algorithms/BFS.h"
#include "algorithms/DFS.h"
#include "algorithms/Dijkstra.h"
#include "algorithms/AStar.h"

int main() {

    Graph graph(5);

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 4, 3);

    // Positions used by A*
    graph.setPosition(0, 0.0, 0.0);
    graph.setPosition(1, 2.0, 2.0);
    graph.setPosition(2, 1.0, 1.0);
    graph.setPosition(3, 3.0, 1.0);
    graph.setPosition(4, 4.0, 0.0);

    graph.print();

    std::cout << '\n';

    std::cout << "Number of vertices: "
              << graph.getVertexCount()
              << '\n';

    // --------------------
    // BFS
    // --------------------

    std::vector<int> bfsResult = bfs(graph, 0);

    std::cout << "\nBFS from vertex 0: ";

    for (int vertex : bfsResult) {
        std::cout << vertex << " ";
    }

    std::cout << '\n';

    // --------------------
    // DFS
    // --------------------

    std::vector<int> dfsResult = dfs(graph, 0);

    std::cout << "DFS from vertex 0: ";

    for (int vertex : dfsResult) {
        std::cout << vertex << " ";
    }

    std::cout << '\n';

    // --------------------
    // Dijkstra
    // --------------------

    DijkstraResult dijkstraResult = dijkstra(graph, 0);

    std::cout << "\nDijkstra from vertex 0:\n";

    for (int vertex = 0;
         vertex < graph.getVertexCount();
         vertex++) {

        std::cout << "Distance to "
                  << vertex
                  << ": "
                  << dijkstraResult.distances[vertex]
                  << '\n';
    }

    int destination = 4;

    std::vector<int> path =
        reconstructPath(
            dijkstraResult,
            0,
            destination
        );

    std::cout << "\nShortest path from 0 to "
              << destination
              << ": ";

    for (int vertex : path) {
        std::cout << vertex << " ";
    }

    std::cout << '\n';

    // --------------------
    // A*
    // --------------------

    AStarResult aStarResult =
        aStar(graph, 0, destination);

    std::cout << "\nA* from vertex 0 to "
              << destination
              << ":\n";

    std::cout << "Distance: "
              << aStarResult.distance
              << '\n';

    std::cout << "Shortest path: ";

    for (int vertex : aStarResult.path) {
        std::cout << vertex << " ";
    }

    std::cout << '\n';

    return 0;
}