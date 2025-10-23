#ifndef CITY_INTEGRATION_MODULE_H
#define CITY_INTEGRATION_MODULE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "../include/patients.h"
#include "admission_module.h"
using namespace std;
struct HospitalNode
{
    int id;
    string name;
    string city;
    int bedsAvailable;
    int totalBeds;

    // Constructor: initializes all fields; city defaults to empty
    HospitalNode(int i = 0, const string &n = "", const string &c = "", int b = 0)
        : id(i), name(n), city(c), bedsAvailable(b), totalBeds(b) {}
};

class CityIntegrationModule
{
private:
    vector<HospitalNode> hospitals;
    vector<vector<int>> distanceMatrix; // adjacency matrix for distances

public:
    CityIntegrationModule(int numHospitals = 0);

    void loadHospitalsFromCSV(const string &path); // Load city & hospital info
    void setDistance(int from, int to, int distance);
    void findNearestHospitalWithBed(Patient &p); // Auto-assign nearest hospital
    void showHospitals() const;
    void addHospital(int id, const string &name, int beds, const string &cityName = "");
    vector<HospitalNode> &getHospitals() { return hospitals; }
    int getHospitalCount() const { return hospitals.size(); }
};

#endif
