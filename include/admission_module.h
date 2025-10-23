#ifndef ADMISSION_MODULE_H
#define ADMISSION_MODULE_H

#include "../include/patients.h"
#include "../include/hash_table.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct HospitalInfo
{
    int id;              // Unique hospital ID
    string city;         // City name
    string hospitalName; // Hospital name
    int totalBeds;       // Total beds in hospital
    int availableBeds;   // Currently available beds

    // Constructor for convenience
    HospitalInfo(int i = 0, const string &c = "", const string &name = "", int total = 0, int avail = 0)
        : id(i), city(c), hospitalName(name), totalBeds(total), availableBeds(avail) {}
};

class AdmissionModule
{
private:
    HashTable beds; // Bed management
    int totalBeds;
    vector<HospitalInfo> hospitals;

public:
    AdmissionModule(int defaultBeds = 20);
    AdmissionModule(const string &csvPath, int defaultBeds = 20);

    void loadHospitalsFromCSV(const string &path);

    bool admitPatient(Patient &p);           // automatically assign bed
    void showBedStatus() const;              // all hospitals
    void showBedStatus(int patientID) const; // for a patient
    HashTable &getBeds() { return beds; }
    const vector<HospitalInfo> &getHospitals() const { return hospitals; }
};

#endif
