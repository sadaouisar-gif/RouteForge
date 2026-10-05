#include "AStar.h"

#include <queue>
#include <vector>
#include <limits>
#include <functional>
#include <cmath>
#include <algorithm>
#include <stdexcept>

double heuristic(
    const Graph& graph,
    int vertex,
    int destination
) {
    Position current = graph.getPosition(vertex);
    Position target = graph.getPosition(destination);

    double dx = target.x - current.x;
    double dy = target.y - current.y;

    return std::sqrt(dx * dx + dy * dy);
}


AStarResult aStar(
    const Graph& graph,
    int startVertex,
    int destination
) {

    if (startVertex < 0 ||
        startVertex >= graph.getVertexCount() ||
        destination < 0 ||
        destination >= graph.getVertexCount()) {

        throw std::out_of_range("Invalid vertex");
    }

    int vertexCount = graph.getVertexCount();

    std::vector<int> distances(
        vertexCount,
        std::numeric_limits<int>::max()
    );

    std::vector<int> previous(vertexCount, -1);

    std::priority_queue<
        std::pair<double, int>,
        std::vector<std::pair<double, int>>,
        std::greater<std::pair<double, int>>
    > priorityQueue;

    distances[startVertex] = 0;

    double startPriority =
        heuristic(graph, startVertex, destination);

    priorityQueue.push({
        startPriority,
        startVertex
    });

    while (!priorityQueue.empty()) {

        int currentVertex =
            priorityQueue.top().second;

        priorityQueue.pop();

        if (currentVertex == destination) {
            break;
        }

        for (const auto& edge :
             graph.getNeighbors(currentVertex)) {

            int neighbor = edge.first;
            int weight = edge.second;

            int newDistance =
                distances[currentVertex] + weight;

            if (newDistance < distances[neighbor]) {

                distances[neighbor] = newDistance;
                previous[neighbor] = currentVertex;

                double priority =
                    newDistance +
                    heuristic(
                        graph,
                        neighbor,
                        destination
                    );

                priorityQueue.push({
                    priority,
                    neighbor
                });
            }
        }
    }

    std::vector<int> path;

    if (distances[destination] ==
        std::numeric_limits<int>::max()) {

        return {path, -1};
    }

    int currentVertex = destination;

    while (currentVertex != -1) {

        path.push_back(currentVertex);

        if (currentVertex == startVertex) {
            break;
        }

        currentVertex =
            previous[currentVertex];
    }

    std::reverse(
        path.begin(),
        path.end()
    );

    return {
        path,
        distances[destination]
    };
}