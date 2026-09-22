#include "BFS.h"
#include <queue>
#include <stdexcept>

std::vector<int> bfs(const Graph& graph, int startVertex) {
    // Vérifier que le sommet de départ existe
    if (startVertex < 0 || startVertex >= graph.getVertexCount()) {
        throw std::out_of_range("Invalid start vertex");
    }

    // Sommets déjà découverts
    std::vector<bool> visited(graph.getVertexCount(), false);

    // La file FIFO utilisée par BFS
    std::queue<int> queue;

    // l'ordre final du parcours
    std::vector<int> traversalOrder;

    // L'initialisation
    visited[startVertex] = true;
    queue.push(startVertex);

    // le parcours BFS
    while (!queue.empty()) {
        int currentVertex = queue.front();
        queue.pop();

        traversalOrder.push_back(currentVertex);

        // Explorer tous les voisins
        for (const auto& edge : graph.getNeighbors(currentVertex)) {
            int neighbor = edge.first;

            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.push(neighbor);
            }
        }
    }

    return traversalOrder;
}