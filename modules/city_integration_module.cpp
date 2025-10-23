#include "../include/city_integartion_module.h"
#include "admission_module.h"
#include <limits>
#include <algorithm>
#include <iostream>
using namespace std;

// Constructor
CityIntegrationModule::CityIntegrationModule(int numHospitals)
{
    hospitals.reserve(numHospitals);
    distanceMatrix.resize(numHospitals, vector<int>(numHospitals, 0));
}

// Load hospital data from CSV
// CSV format: id,name,city,totalBeds
void CityIntegrationModule::loadHospitalsFromCSV(const string &path)
{
    ifstream file(path);
    if (!file)
    {
        cout << "Error: Could not open " << path << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header

    int index = 0;
    while (getline(file, line))
    {
        stringstream ss(line);
        string idStr, name, city, bedsStr;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, city, ',');
        getline(ss, bedsStr, ',');

        int id = stoi(idStr);
        int beds = stoi(bedsStr);

        HospitalNode h(id, name, city, beds);
        hospitals.push_back(h);

        index++;
    }

    // Initialize distance matrix with 0
    int n = hospitals.size();
    distanceMatrix.resize(n, vector<int>(n, 0));
}

// Set distance between hospitals
void CityIntegrationModule::setDistance(int from, int to, int distance)
{
    if (from >= 0 && from < hospitals.size() && to >= 0 && to < hospitals.size())
    {
        distanceMatrix[from][to] = distance;
        distanceMatrix[to][from] = distance; // symmetric
    }
}

// Find nearest hospital with available bed
void CityIntegrationModule::findNearestHospitalWithBed(Patient &p)
{
    int nearestID = -1;
    int minDist = numeric_limits<int>::max();

    for (size_t i = 0; i < hospitals.size(); i++)
    {
        if (hospitals[i].bedsAvailable > 0)
        {
            // Compute simple "distance" metric if location is available
            // Currently just pick the first available if no real distance
            nearestID = i;
            break;
        }
    }

    if (nearestID != -1)
    {
        hospitals[nearestID].bedsAvailable--;

        // Assign hospital info to patient
        p.setAssignedHospital(hospitals[nearestID].name);
        p.setAssignedBedID(hospitals[nearestID].totalBeds - hospitals[nearestID].bedsAvailable);

        cout << "🏥 Patient " << p.getName() << " allocated to "
             << p.getAssignedHospital() << ", Bed ID: "
             << p.getAssignedBedID() << endl;
    }
    else
    {
        cout << "⚠️ No beds available in any hospital currently. "
             << p.getName() << " is added to waiting list.\n";
    }
}

// Display hospital status
void CityIntegrationModule::showHospitals() const
{
    cout << "\n===== City Hospitals Status =====\n";
    for (const auto &h : hospitals)
    {
        cout << "Hospital: " << h.name
             << " | City: " << h.city
             << " | Total Beds: " << h.totalBeds
             << " | Available Beds: " << h.bedsAvailable << endl;
    }
    cout << "================================\n";
}
void CityIntegrationModule::addHospital(int id, const string &name, int beds, const string &cityName)
{
    hospitals.emplace_back(id, name, cityName, beds);

    // Resize distance matrix dynamically
    int n = hospitals.size();
    distanceMatrix.resize(n);
    for (auto &row : distanceMatrix)
        row.resize(n, 0);
}
