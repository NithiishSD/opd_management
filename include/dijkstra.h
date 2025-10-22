#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <utility>
#include <limits>
using namespace std;

class Dijkstra
{
private:
    int numVertices;
    vector<vector<pair<int, int>>> adjacencyList;

public:
    Dijkstra(int vertices);
    void addEdge(int source, int destination, int distance);
    vector<int> shortestPath(int startNode);
};

#endif
