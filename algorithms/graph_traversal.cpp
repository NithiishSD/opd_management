#include "../include/graph.h"
#include <iostream>
using namespace std;

// Constructor: Initialize graph with given number of vertices
Graph::Graph(int V)
{
    this->vertices = V;
    adjacencyList.resize(V);
}

// Adds an edge between two nodes (bi-directional)
void Graph::addEdge(int src, int dest, int weight)
{
    if (src >= vertices || dest >= vertices || src < 0 || dest < 0)
    {
        cout << " Invalid node index. Cannot add edge (" << src << " ↔ " << dest << ")." << endl;
        return;
    }

    adjacencyList[src].push_back({dest, weight});
    adjacencyList[dest].push_back({src, weight});
}

void Graph::displayGraph() const
{
    cout << "\n🌐 City Hospital Graph Structure:\n";
    for (int i = 0; i < vertices; i++)
    {
        cout << "Node " << i << " → ";
        for (auto &edge : adjacencyList[i])
        {
            cout << "(Dest: " << edge.first << ", Dist: " << edge.second << ")  ";
        }
        cout << endl;
    }
}

const vector<pair<int, int>> &Graph::getNeighbors(int node) const
{
    if (node >= vertices || node < 0)
    {
        cout << " Invalid node index in getNeighbors(). Returning empty list.\n";
        static vector<pair<int, int>> empty;
        return empty;
    }
    return adjacencyList[node];
}

int Graph::getVertices() const
{
    return vertices;
}
