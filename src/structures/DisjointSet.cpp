#include "DisjointSet.h"

DisjointSet::DisjointSet(int size) {

    parent.resize(size);
    rank.resize(size, 0);

    for (int vertex = 0; vertex < size; vertex++) {
        parent[vertex] = vertex;
    }
}


int DisjointSet::find(int vertex) {

    if (parent[vertex] != vertex) {

        parent[vertex] =
            find(parent[vertex]);
    }

    return parent[vertex];
}


bool DisjointSet::unite(
    int vertexA,
    int vertexB
) {

    int rootA = find(vertexA);
    int rootB = find(vertexB);

    // Already in the same set:
    // adding the edge would create a cycle.
    if (rootA == rootB) {
        return false;
    }

    // Union by rank
    if (rank[rootA] < rank[rootB]) {

        parent[rootA] = rootB;

    } else if (rank[rootA] > rank[rootB]) {

        parent[rootB] = rootA;

    } else {

        parent[rootB] = rootA;
        rank[rootA]++;
    }

    return true;
}