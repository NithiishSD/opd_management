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

    HashTable<Patient *> beds; // bedid,Patient

public:
    Hospital() = default;
    Hospital(int id, const std::string &name, const std::string &location, int bedCount);

    int getHospitalID() const;
    std::string getHospitalName() const;
    std::string getLocationName() const;
    int getTotalBeds() const;

    int assignBed(Patient &p);
    bool freeBed(int bedID);
    std::vector<int> getOccupiedBeds() const;
    Patient *getPatientByBed(int patientID);
};

#endif
