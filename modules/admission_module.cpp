#include "../include/admission_module.h"
#include "../include/utils.h"
#include <iostream>

using namespace std;
AdmissionModule::AdmissionModule(const std::vector<Hospital *> &hospList)
{
    hospitals = hospList;
}

bool AdmissionModule::admitPatient(Patient &p)
{
    for (auto &h : hospitals)
    {
        int bedID = h->assignBed(p);
        if (bedID != -1)
        {
            p.setHospitalID(h->getHospitalID());
            p.setBedID(bedID);
            p.setStatus("Admitted");
            cout << "Patient " << p.getName() << " (ID: " << p.getPatientID() << ") admitted to:\n";
            cout << "Hospital ID: " << h->getHospitalID() << " (" << h->getHospitalName() << ")\n";
            cout << "Bed ID: " << bedID << "\n";
            return true;
        }
    }
    return false;
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
