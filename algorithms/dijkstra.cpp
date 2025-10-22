#include "dijkstra.h"
#include <iostream>
using namespace std;

Dijkstra::Dijkstra(int vertices)
{
    numVertices = vertices;
    adjacencyList.resize(vertices);
}

void Dijkstra::addEdge(int source, int destination, int distance)
{
    adjacencyList[source].push_back({destination, distance});
    adjacencyList[destination].push_back({source, distance});
}

vector<int> Dijkstra::shortestPath(int startNode)
{
    vector<int> distance(numVertices, INT_MAX);
    vector<bool> visited(numVertices, false);

    distance[startNode] = 0;

    for (int count = 0; count < numVertices - 1; count++)
    {
        int minIndex = -1;
        int minDistance = INT_MAX;

        for (int i = 0; i < numVertices; i++)
        {
            if (!visited[i] && distance[i] < minDistance)
            {
                minDistance = distance[i];
                minIndex = i;
            }
        }

        if (minIndex == -1)
            break;

        visited[minIndex] = true;

        for (auto &neighbor : adjacencyList[minIndex])
        {
            int nextNode = neighbor.first;
            int edgeWeight = neighbor.second;

            if (!visited[nextNode] && distance[minIndex] != INT_MAX &&
                distance[minIndex] + edgeWeight < distance[nextNode])
            {
                distance[nextNode] = distance[minIndex] + edgeWeight;
            }
        }
    }

    return distance;
}
