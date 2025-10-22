#include "../include/city_integartion_module.h"
#include <queue>
using namespace std;

CityIntegrationModule::CityIntegrationModule(int totalHospitals)
{
    hospitals.resize(totalHospitals);
    adjMatrix.resize(totalHospitals, vector<int>(totalHospitals, -1));
}

void CityIntegrationModule::addHospital(int id, const string &name, int beds)
{
    hospitals[id] = HospitalNode(id, name, beds);
}

void CityIntegrationModule::setDistance(int fromID, int toID, int distance)
{
    adjMatrix[fromID][toID] = distance;
    adjMatrix[toID][fromID] = distance;
}

int CityIntegrationModule::findNearestHospitalWithBed(const Patient &p)
{
    int n = hospitals.size();
    vector<int> dist(n, numeric_limits<int>::max());
    vector<bool> visited(n, false);

    dist[0] = 0;

    for (int count = 0; count < n; count++)
    {
        int u = -1;
        int minDist = numeric_limits<int>::max();
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && dist[i] < minDist)
            {
                u = i;
                minDist = dist[i];
            }
        }
        if (u == -1)
            break;
        visited[u] = true;

        for (int v = 0; v < n; v++)
        {
            if (adjMatrix[u][v] != -1 && !visited[v])
            {
                if (dist[u] + adjMatrix[u][v] < dist[v])
                {
                    dist[v] = dist[u] + adjMatrix[u][v];
                }
            }
        }
    }

    // Find nearest hospital with available bed
    int nearestID = -1;
    int minDistance = numeric_limits<int>::max();
    for (int i = 0; i < n; i++)
    {
        if (hospitals[i].bedsAvailable > 0 && dist[i] < minDistance)
        {
            minDistance = dist[i];
            nearestID = i;
        }
    }

    if (nearestID != -1)
    {
        cout << "[CityIntegration] Nearest hospital with available bed for "
             << p.getName() << " is " << hospitals[nearestID].name
             << " (Distance: " << minDistance << ")\n";
        hospitals[nearestID].bedsAvailable--;
    }
    else
    {
        cout << "[CityIntegration] No hospital available for " << p.getName() << "\n";
    }

    return nearestID;
}

void CityIntegrationModule::showHospitals() const
{
    cout << "[CityIntegration] Hospitals info:\n";
    for (const auto &h : hospitals)
        cout << "ID:" << h.id << " Name:" << h.name
             << " Available beds:" << h.bedsAvailable << "\n";
}
