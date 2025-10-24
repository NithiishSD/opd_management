#include "../include/admission_module.h"
#include "../include/utils.h"
#include <iostream>

using namespace std;

AdmissionModule::AdmissionModule(const vector<Hospital> &hospList)
{
    hospitals = hospList;
}

// Admit patient to the first available bed in any hospital
bool AdmissionModule::admitPatient(Patient &p)
{
    for (auto &h : hospitals)
    {
        int bedID = h.assignBed(p);
        if (bedID != -1)
        {
            p.setHospitalID(h.getHospitalID());
            p.setBedID(bedID);
            p.setStatus("Admitted");

            return true; // Successfully admitted
        }
    }
    return false; // No beds available
}

// Find patient by ID in all hospitals
Patient *AdmissionModule::findPatientByID(int id)
{
    for (auto &h : hospitals)
    {
        Patient *p = h.getPatientByBed(id);
        if (p != nullptr)
            return p;
    }
    return nullptr;
}

// Return all hospitals (for city integration)
vector<Hospital> &AdmissionModule::getHospitals()
{
    return hospitals;
}

// Return all occupied beds as HospitalID, BedID pairs
vector<pair<int, int>> AdmissionModule::getBeds() const
{
    vector<pair<int, int>> result;
    for (const auto &h : hospitals)
    {
        vector<int> beds = h.getOccupiedBeds();
        for (int bed : beds)
        {
            result.push_back({h.getHospitalID(), bed});
        }
    }
    return result;
}

// Display bed status of all hospitals
void AdmissionModule::showBedStatus() const
{
    cout << "=== Hospital Bed Status ===\n";
    for (const auto &h : hospitals)
    {
        cout << "Hospital " << h.getHospitalName() << " (ID: " << h.getHospitalID() << ")\n";
        vector<int> beds = h.getOccupiedBeds();
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
