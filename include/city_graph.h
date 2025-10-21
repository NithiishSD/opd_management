#ifndef city_graph_h
#define city_graph_h

#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
using namespace std;

struct Edge
{
    int to;
    int distance;
};

class CityGraph
{
private:
    unordered_map<int, vector<Edge>> adjacencyList;

public:
    void addHospital(int hospitalID);
    void addConnection(int from, int to, int distance);
    vector<Edge> getConnections(int hospitalID) const;

    int findNearestHospital(int sourceID, const unordered_map<int, int> &availability);
};

#endif
