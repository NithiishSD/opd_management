#ifndef CITY_INTEGRATION_H
#define CITY_INTEGRATION_H

#include "../include/hash_table.h"
#include "../include/patients.h"
#include <vector>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

// Simple structure for hospital nodes in the city
struct HospitalNode
{
    string name;
    int bedsAvailable;
    int id; // Unique hospital ID
    HospitalNode(int i = 0, string n = "", int b = 0) : id(i), name(n), bedsAvailable(b) {}
};

class CityIntegrationModule
{
    vector<HospitalNode> hospitals;
    vector<vector<int>> adjMatrix; // distance between hospitals

public:
    CityIntegrationModule(int totalHospitals);

    void addHospital(int id, const string &name, int beds);
    void setDistance(int fromID, int toID, int distance);
    int findNearestHospitalWithBed(const Patient &p);
    void showHospitals() const;
};

#endif
