#include "Dijkstra.h"

#include <queue>
#include <limits>
#include <functional>
#include <stdexcept>
#include <algorithm>

DijkstraResult dijkstra(const Graph& graph, int startVertex) {

    if (startVertex < 0 || startVertex >= graph.getVertexCount()) {
        throw std::out_of_range("Invalid start vertex");
    }

    int vertexCount = graph.getVertexCount();

    // Distance minimale connue vers chaque sommet
    std::vector<int> distances(
        vertexCount,
        std::numeric_limits<int>::max()
    );

    // Sommet précédent utilisé pour atteindre chaque sommet
    std::vector<int> previous(vertexCount, -1);

    // Min-heap contenant : {distance, vertex}
    std::priority_queue<
        std::pair<int, int>,
        std::vector<std::pair<int, int>>,
        std::greater<std::pair<int, int>>
    > priorityQueue;

    distances[startVertex] = 0;
    priorityQueue.push({0, startVertex});

    while (!priorityQueue.empty()) {

        int currentDistance = priorityQueue.top().first;
        int currentVertex = priorityQueue.top().second;

        priorityQueue.pop();

        if (currentDistance > distances[currentVertex]) {
            continue;
        }

        for (const auto& edge : graph.getNeighbors(currentVertex)) {

            int neighbor = edge.first;
            int weight = edge.second;

            int newDistance = currentDistance + weight;

            if (newDistance < distances[neighbor]) {

                distances[neighbor] = newDistance;

                // Mémoriser d'où on vient
                previous[neighbor] = currentVertex;

                priorityQueue.push({
                    newDistance,
                    neighbor
                });
            }
        }
    }

    return {distances, previous};
}


std::vector<int> reconstructPath(
    const DijkstraResult& result,
    int startVertex,
    int destination
) {
    std::vector<int> path;

    int currentVertex = destination;

    while (currentVertex != -1) {

        path.push_back(currentVertex);

        if (currentVertex == startVertex) {
            break;
        }

        currentVertex = result.previous[currentVertex];
    }

    // Aucun chemin trouvé
    if (path.empty() || path.back() != startVertex) {
        return {};
    }

    // On a construit destination -> ... -> start
    // On inverse pour obtenir start -> ... -> destination
    std::reverse(path.begin(), path.end());

    return path;
}