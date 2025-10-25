#ifndef CITY_INTEGRATION_MODULE_H
#define CITY_INTEGRATION_MODULE_H
#include "patients.h"
#include "hospital.h"
#include "city_graph.h" // Add this include
#include <vector>
#include <string>

class CityIntegrationModule {
private:
    std::vector<Hospital *> hospitals;
    CityGraph graph; // Add CityGraph to store hospital connections

public:
    CityIntegrationModule() = default;
    CityIntegrationModule(const std::vector<Hospital *> &hospitalList);
    void initializeGraph(const std::vector<Hospital> &hospitals); // New method
    Hospital *assignPatientToNearestHospital(Patient &p);
    std::string getHospitalName(int hospitalID) const;
};
#endif