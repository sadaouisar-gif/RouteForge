#include <iostream>
#include <vector>

#include "graph/Graph.h"
#include "algorithms/BFS.h"
#include "algorithms/DFS.h"
#include "algorithms/Dijkstra.h"
#include "algorithms/AStar.h"
#include "algorithms/BellmanFord.h"
#include "algorithms/Prim.h"
#include "algorithms/Kruskal.h"

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

    DijkstraResult dijkstraResult =
        dijkstra(graph, 0);

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

    // --------------------
    // Bellman-Ford
    // --------------------

    BellmanFordResult bellmanResult =
        bellmanFord(graph, 0);

    std::cout << "\nBellman-Ford from vertex 0:\n";

    if (bellmanResult.hasNegativeCycle) {

        std::cout << "Negative cycle detected!\n";

    } else {

        for (int vertex = 0;
             vertex < graph.getVertexCount();
             vertex++) {

            std::cout << "Distance to "
                      << vertex
                      << ": "
                      << bellmanResult.distances[vertex]
                      << '\n';
        }

        std::vector<int> bellmanPath =
            reconstructBellmanFordPath(
                bellmanResult,
                0,
                destination
            );

        std::cout << "Shortest path from 0 to "
                  << destination
                  << ": ";

        for (int vertex : bellmanPath) {
            std::cout << vertex << " ";
        }

        std::cout << '\n';
    }

    // --------------------
// Bellman-Ford with negative weight
// --------------------

std::cout << "\n--- Bellman-Ford negative weight test ---\n";

Graph negativeGraph(4, true);

negativeGraph.addEdge(0, 1, 4);
negativeGraph.addEdge(0, 2, 5);
negativeGraph.addEdge(1, 2, -2);
negativeGraph.addEdge(2, 3, 3);

BellmanFordResult negativeResult =
    bellmanFord(negativeGraph, 0);

if (negativeResult.hasNegativeCycle) {

    std::cout << "Negative cycle detected!\n";

} else {

    for (int vertex = 0;
         vertex < negativeGraph.getVertexCount();
         vertex++) {

        std::cout << "Distance to "
                  << vertex
                  << ": "
                  << negativeResult.distances[vertex]
                  << '\n';
    }

    std::vector<int> negativePath =
        reconstructBellmanFordPath(
            negativeResult,
            0,
            3
        );

    std::cout << "Shortest path from 0 to 3: ";

    for (int vertex : negativePath) {
        std::cout << vertex << " ";
    }

   std::cout << '\n';
}

// --------------------
// Negative cycle test
// --------------------

std::cout << "\n--- Negative cycle test ---\n";

Graph cycleGraph(3, true);

cycleGraph.addEdge(0, 1, 1);
cycleGraph.addEdge(1, 2, -2);
cycleGraph.addEdge(2, 1, -2);

BellmanFordResult cycleResult =
    bellmanFord(cycleGraph, 0);

if (cycleResult.hasNegativeCycle) {
    std::cout << "Negative cycle detected!\n";
} else {
    std::cout << "No negative cycle detected.\n";
}


// --------------------
// Prim
// --------------------

std::cout << "\n--- Prim MST test ---\n";

PrimResult primResult = prim(graph, 0);

if (!primResult.connected) {

    std::cout << "The graph is not connected.\n";

} else {

    std::cout << "MST edges:\n";

    for (const MSTEdge& edge : primResult.edges) {

        std::cout << edge.source
                  << " -> "
                  << edge.destination
                  << " | weight: "
                  << edge.weight
                  << '\n';
    }

    std::cout << "Total MST weight: "
              << primResult.totalWeight
              << '\n';
}

// --------------------
// Kruskal
// --------------------

std::cout << "\n--- Kruskal MST test ---\n";

KruskalResult kruskalResult = kruskal(graph);

if (!kruskalResult.connected) {

    std::cout << "The graph is not connected.\n";

} else {

    std::cout << "MST edges:\n";

    for (const MSTEdge& edge : kruskalResult.edges) {

        std::cout << edge.source
                  << " -> "
                  << edge.destination
                  << " | weight: "
                  << edge.weight
                  << '\n';
    }

    std::cout << "Total MST weight: "
              << kruskalResult.totalWeight
              << '\n';
}

// --------------------
// Compare Prim and Kruskal
// --------------------

std::cout << "\n--- MST Comparison ---\n";

std::cout << "Prim total weight: "
          << primResult.totalWeight
          << '\n';

std::cout << "Kruskal total weight: "
          << kruskalResult.totalWeight
          << '\n';

if (primResult.connected &&
    kruskalResult.connected &&
    primResult.totalWeight == kruskalResult.totalWeight) {

    std::cout << "Both algorithms agree!\n";

} else {

    std::cout << "MST comparison requires verification.\n";
}

    return 0;
}