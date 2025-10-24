#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "patients.h"
#include "hash_table.h"
#include <vector>
#include <string>

class Hospital
{
private:
    int hospitalID;
    std::string hospitalName;
    std::string locationName;
    int totalBeds;

    HashTable<Patient *> beds; // Custom hash table: BedID -> Patient

public:
    Hospital() = default;
    Hospital(int id, const std::string &name, const std::string &location, int bedCount);

    int getHospitalID() const;
    std::string getHospitalName() const;
    std::string getLocationName() const;
    int getTotalBeds() const;

    int assignBed(Patient &p);                // Assign patient to a free bed, return BedID or -1
    bool freeBed(int bedID);                  // Free bed
    std::vector<int> getOccupiedBeds() const; // List of occupied beds
    Patient *getPatientByBed(int patientID);  // Find patient by ID
};

#endif
