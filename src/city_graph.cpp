#include "../include/city_graph.h"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <climits>
using namespace std;

// ------------------- Add Hospital -------------------
void CityGraph::addHospital(int hospitalID) {
    if (adjacencyList.find(hospitalID) == adjacencyList.end()) {
        adjacencyList[hospitalID] = vector<Edge>();
    }
}

// ------------------- Add Connection -------------------
void CityGraph::addConnection(int from, int to, int distance) {
    adjacencyList[from].push_back({to, distance});
    adjacencyList[to].push_back({from, distance}); // undirected
}

// ------------------- Get Connections -------------------
vector<Edge> CityGraph::getConnections(int hospitalID) const {
    if (adjacencyList.find(hospitalID) != adjacencyList.end()) {
        return adjacencyList.at(hospitalID);
    }
    return vector<Edge>();
}

// ------------------- Find Nearest Hospital -------------------
// Returns hospitalID of nearest hospital with available beds
int CityGraph::findNearestHospital(int sourceID, const unordered_map<int, int> &availability) {
    // Dijkstra's algorithm
    unordered_map<int, int> dist;
    for (auto &pair : adjacencyList) {
        dist[pair.first] = INT_MAX;
    }

    dist[sourceID] = 0;

    // Min-heap: pair<distance, hospitalID>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, sourceID});

    while (!pq.empty()) {
        auto [currentDist, u] = pq.top();
        pq.pop();

        if (availability.find(u) != availability.end() && availability.at(u) > 0) {
            return u; // nearest hospital with free bed found
        }

        for (auto &edge : adjacencyList[u]) {
            int v = edge.to;
            int w = edge.distance;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return -1; // no available hospital found
}
