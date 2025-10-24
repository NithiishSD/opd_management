#ifndef CITY_GRAPH_H

#define CITY_GRAPH_H

#include <vector>
#include <unordered_map>

struct Edge
{
    int to;
    int distance;
};

class CityGraph
{
private:
    std::unordered_map<int, std::vector<Edge>> adjacencyList;

public:
    void addHospital(int hospitalID);
    void addConnection(int from, int to, int distance);
    std::vector<Edge> getConnections(int hospitalID) const;
    int findNearestHospital(int sourceID, const std::unordered_map<int, int> &availability);
};

#endif
