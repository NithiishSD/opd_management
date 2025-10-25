#include "dijkstra.h"
#include <queue>
#include <climits>

Dijkstra::Dijkstra(const vector<int> &hospitalIds) {
    numVertices = hospitalIds.size();
    adjacencyList.resize(numVertices);
    for (size_t i = 0; i < hospitalIds.size(); ++i) {
        idToIndex[hospitalIds[i]] = i;
        indexToId[i] = hospitalIds[i];
    }
}

void Dijkstra::addEdge(int source, int destination, int distance) {
    if (idToIndex.find(source) == idToIndex.end() || idToIndex.find(destination) == idToIndex.end()) {
        return; // Invalid hospital ID
    }
    int srcIndex = idToIndex[source];
    int destIndex = idToIndex[destination];
    adjacencyList[srcIndex].push_back({destIndex, distance});
    adjacencyList[destIndex].push_back({srcIndex, distance});
}

vector<pair<int, int>> Dijkstra::shortestPath(int startNode) {
    if (idToIndex.find(startNode) == idToIndex.end()) {
        return {}; // Invalid start node
    }
    int startIndex = idToIndex[startNode];
    vector<int> distance(numVertices, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    distance[startIndex] = 0;
    pq.push({0, startIndex});

    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (dist > distance[u]) continue;

        for (auto &neighbor : adjacencyList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                pq.push({distance[v], v});
            }
        }
    }

    vector<pair<int, int>> result;
    for (int i = 0; i < numVertices; ++i) {
        if (distance[i] != INT_MAX) {
            result.emplace_back(indexToId[i], distance[i]);
        }
    }
    return result;
}