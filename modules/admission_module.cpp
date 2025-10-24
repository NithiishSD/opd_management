#include "../include/admission_module.h"
#include "../include/utils.h"
#include "../include/city_integration_module.h"
#include <iostream>

using namespace std;
AdmissionModule::AdmissionModule(const std::vector<Hospital *> &hospList)
{
    hospitals = hospList;
}

bool AdmissionModule::admitPatient(Patient &p, CityIntegrationModule &city)
{
    Hospital *assignedHospital = city.assignPatientToNearestHospital(p);
    if (!assignedHospital)
    {
        std::cout << "[Admission] No valid hospital found for patient " << p.getName() << "\n";
        return false;
    }
    return true;
    // if (bedID != -1)
    // {
    //     p.setHospitalID(assignedHospital->getHospitalID());
    //     p.setBedID(bedID);
    //     p.setStatus("Admitted");
    //     std::cout << "Patient " << p.getName() << " (ID: " << p.getPatientID() << ") admitted to:\n";
    //     std::cout << "Hospital ID: " << assignedHospital->getHospitalID() << " (" << assignedHospital->getHospitalName() << ")\n";
    //     std::cout << "Bed ID: " << bedID << "\n";
    //     return true;
    // }
}

Patient *AdmissionModule::findPatientByID(int id)
{
    for (auto &h : hospitals)
    {
        Patient *p = h->getPatientByBed(id);
        if (p != nullptr)
            return p;
    }
    return nullptr;
}

vector<Hospital *> &AdmissionModule::getHospitals()
{
    return hospitals;
}

vector<pair<int, int>> AdmissionModule::getBeds() const
{
    vector<pair<int, int>> result;
    for (const auto &h : hospitals)
    {
        vector<int> beds = h->getOccupiedBeds();
        for (int bed : beds)
        {
            result.push_back({h->getHospitalID(), bed});
        }
    }
    return result;
}

void AdmissionModule::showBedStatus() const
{
    cout << "=== Hospital Bed Status ===\n";
    for (const auto &h : hospitals)
    {
        cout << "Hospital " << h->getHospitalName() << " (ID: " << h->getHospitalID() << ")\n";
        vector<int> beds = h->getOccupiedBeds();
        cout << "Occupied Beds: ";
        if (beds.empty())
        {
            cout << "None";
        }
        else
        {
            for (int bed : beds)
                cout << bed << " ";
        }
        cout << "\n";
    }
}
