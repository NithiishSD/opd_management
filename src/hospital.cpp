#include "../include/hospital.h"
#include <iostream>
#include <algorithm>

using namespace std;

Hospital::Hospital(int id, const string &name, const string &location, int bedCount)
    : hospitalID(id), hospitalName(name), locationName(location), totalBeds(bedCount), beds(bedCount)
{
    // Initialize hash table with capacity = totalBeds
}

// Getters
int Hospital::getHospitalID() const { return hospitalID; }
int Hospital::getTotalBeds() const { return totalBeds; }
string Hospital::getHospitalName() const { return hospitalName; }
string Hospital::getLocationName() const { return locationName; }

// Assign patient to a free bed using hash table
int Hospital::assignBed(Patient &p)
{
    for (int i = 1; i <= totalBeds; i++)
    {
        if (!beds.exists(i))
        { // Bed free
            beds.insert(i, &p);
            totalBeds--; // BedID -> Patient
            return i;
        }
    }
    return -1; // No bed available
}

// Free a bed
bool Hospital::freeBed(int bedID)
{
    if (beds.exists(bedID))
    {
        beds.remove(bedID);
        return true;
    }
    return false;
}

// Get list of occupied beds
vector<int> Hospital::getOccupiedBeds() const
{
    vector<int> occupied;
    for (int i = 1; i <= totalBeds; i++)
    {
        if (beds.exists(i))
            occupied.push_back(i);
    }
    return occupied;
}

// Find patient by ID
Patient *Hospital::getPatientByBed(int patientID)
{
    for (int i = 1; i <= totalBeds; i++)
    {
        if (beds.exists(i))
        {
            Patient *p = *beds.get(i);
            if (p != nullptr && p->getPatientID() == patientID)
                return p;
        }
    }
    return nullptr;
}
