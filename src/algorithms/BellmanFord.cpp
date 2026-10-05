#include "BellmanFord.h"

#include <limits>
#include <stdexcept>
#include <algorithm>

BellmanFordResult bellmanFord(
    const Graph& graph,
    int startVertex
) {

    if (startVertex < 0 ||
        startVertex >= graph.getVertexCount()) {

        throw std::out_of_range("Invalid start vertex");
    }

    int vertexCount = graph.getVertexCount();

    std::vector<int> distances(
        vertexCount,
        std::numeric_limits<int>::max()
    );

    std::vector<int> previous(
        vertexCount,
        -1
    );

    distances[startVertex] = 0;

    // Relax all edges V - 1 times
    for (int i = 0; i < vertexCount - 1; i++) {

        bool updated = false;

        for (int vertex = 0;
             vertex < vertexCount;
             vertex++) {

            if (distances[vertex] ==
                std::numeric_limits<int>::max()) {
                continue;
            }

            for (const auto& edge :
                 graph.getNeighbors(vertex)) {

                int neighbor = edge.first;
                int weight = edge.second;

                int newDistance =
                    distances[vertex] + weight;

                if (newDistance <
                    distances[neighbor]) {

                    distances[neighbor] =
                        newDistance;

                    previous[neighbor] =
                        vertex;

                    updated = true;
                }
            }
        }

        // No modification = algorithm already finished
        if (!updated) {
            break;
        }
    }

    // Check for negative cycles
    bool hasNegativeCycle = false;

    for (int vertex = 0;
         vertex < vertexCount;
         vertex++) {

        if (distances[vertex] ==
            std::numeric_limits<int>::max()) {
            continue;
        }

        for (const auto& edge :
             graph.getNeighbors(vertex)) {

            int neighbor = edge.first;
            int weight = edge.second;

            if (distances[vertex] + weight <
                distances[neighbor]) {

                hasNegativeCycle = true;
                break;
            }
        }

        if (hasNegativeCycle) {
            break;
        }
    }

    return {
        distances,
        previous,
        hasNegativeCycle
    };
}


std::vector<int> reconstructBellmanFordPath(
    const BellmanFordResult& result,
    int startVertex,
    int destination
) {

    std::vector<int> path;

    if (result.hasNegativeCycle) {
        return path;
    }

    if (destination < 0 ||
        destination >=
            static_cast<int>(result.distances.size())) {

        throw std::out_of_range(
            "Invalid destination"
        );
    }

    if (result.distances[destination] ==
        std::numeric_limits<int>::max()) {

        return path;
    }

    int currentVertex = destination;

    while (currentVertex != -1) {

        path.push_back(currentVertex);

        if (currentVertex == startVertex) {
            break;
        }

        currentVertex =
            result.previous[currentVertex];
    }

    if (path.empty() ||
        path.back() != startVertex) {

        return {};
    }

    std::reverse(
        path.begin(),
        path.end()
    );

    return path;
}