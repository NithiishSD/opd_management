#ifndef CITY_INTEGRATION_MODULE_H
#define CITY_INTEGRATION_MODULE_H

#include "patients.h"
#include "hospital.h"
#include <vector>
#include <string>

class CityIntegrationModule
{
private:
    std::vector<Hospital> hospitals;

public:
    CityIntegrationModule() = default;

    // Initialize with a list of hospitals
    CityIntegrationModule(const std::vector<Hospital> &hospitalList);

    // Add a new hospital to the city
    void addHospital(const Hospital &h);

    // Assign patient to nearest hospital using greedy allocation
    bool assignPatientToNearestHospital(Patient &p);

    // Display the status of all hospitals and their beds
    void showAllHospitalBeds() const;

    // Get hospital name by ID
    std::string getHospitalName(int hospitalID) const;
};

#endif
