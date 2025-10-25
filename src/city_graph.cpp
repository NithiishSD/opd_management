#include "../include/city_graph.h"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <climits>
using namespace std;

void CityGraph::addHospital(int hospitalID) {
    if (adjacencyList.find(hospitalID) == adjacencyList.end()) {
        adjacencyList[hospitalID] = vector<Edge>();
    }
}

void CityGraph::addConnection(int from, int to, int distance) {
    adjacencyList[from].push_back({to, distance});
    adjacencyList[to].push_back({from, distance}); // undirected
}

vector<Edge> CityGraph::getConnections(int hospitalID) const {
    if (adjacencyList.find(hospitalID) != adjacencyList.end()) {
        return adjacencyList.at(hospitalID);
    }
    return vector<Edge>();
}

int CityGraph::findNearestHospital(int sourceID, const unordered_map<int, int> &availability) {
    unordered_map<int, int> dist;
    for (auto &pair : adjacencyList) {
        dist[pair.first] = INT_MAX;
    }

    dist[sourceID] = 0;

    // Min-heap:
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, sourceID});

    while (!pq.empty()) {
        // Extract currentDist and u without structured binding
        //int currentDist = pq.top().first;
        int u = pq.top().second;
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

    return -1;
}