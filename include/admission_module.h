#ifndef ADMISSION_MODULE_H
#define ADMISSION_MODULE_H

#include "../include/patients.h"
#include "../include/hash_table.h"
#include <iostream>
using namespace std;

class AdmissionModule
{
    HashTable beds; // Custom hash table for bed management
    int totalBeds;  // Track total beds internally
public:
    AdmissionModule(int totalBeds = 20);

    bool admitPatient(Patient &p);           // Admit patient and assign bed
    void showBedStatus() const;              // Display current bed allocation
    void showBedStatus(int patientID) const; // overload
    HashTable &getBeds() { return beds; }
};

#endif
