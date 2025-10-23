#ifndef CITY_INTEGRATION_MODULE_H
#define CITY_INTEGRATION_MODULE_H

#include <iostream>
#include <vector>
#include <string>
#include "../include/patients.h"
using namespace std;

struct HospitalNode
{
    string name;
    int id;
    int bedsAvailable;

    // Match declaration order with initialization order
    HospitalNode(int i = 0, string n = "", int b = 0)
        : name(n), id(i), bedsAvailable(b) {}
};

class CityIntegrationModule
{
private:
    vector<HospitalNode> hospitals;
    vector<vector<int>> distanceMatrix; // adjacency matrix for distances

public:
    CityIntegrationModule(int numHospitals = 3);

    void addHospital(int id, const string &name, int beds);
    void setDistance(int from, int to, int distance);
    void findNearestHospitalWithBed(const Patient &p);
    void showHospitals() const;
};

#endif
