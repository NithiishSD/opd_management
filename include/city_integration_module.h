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

    CityIntegrationModule(const std::vector<Hospital> &hospitalList);

    // void addHospital(const Hospital &h);

    bool assignPatientToNearestHospital(Patient &p);

    // void showAllHospitalBeds() const;

    std::string getHospitalName(int hospitalID) const;
};

#endif
