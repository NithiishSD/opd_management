#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
using namespace std;

class Graph
{
private:
    int vertices;
    vector<vector<pair<int, int>>> adjacencyList;

public:
    Graph(int V);
    void addEdge(int src, int dest, int weight);
    void displayGraph() const;
    const vector<pair<int, int>> &getNeighbors(int node) const;
    int getVertices() const;
};

#endif
