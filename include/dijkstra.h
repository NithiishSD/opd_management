#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <vector>
#include <utility>
#include <unordered_map>
using namespace std;

class Dijkstra {
private:
    int numVertices;
    vector<vector<pair<int, int>>> adjacencyList;
    unordered_map<int, int> idToIndex; // Map hospital ID to index
    unordered_map<int, int> indexToId; // Map index to hospital ID

public:
    Dijkstra(const vector<int> &hospitalIds); // Accept hospital IDs
    void addEdge(int source, int destination, int distance);
    vector<pair<int, int>> shortestPath(int startNode); // Return hospital ID and distance
};
#endif