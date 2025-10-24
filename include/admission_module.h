#ifndef ADMISSION_MODULE_H
#define ADMISSION_MODULE_H

#include "hospital.h"
#include "patients.h"
#include <vector>

class AdmissionModule
{
private:
    std::vector<Hospital *> hospitals;

public:
    AdmissionModule() = default;
    AdmissionModule(const std::vector<Hospital *> &hospList);

    bool admitPatient(Patient &p);                    // Assign patient to a bed
    Patient *findPatientByID(int id);                 // Find patient by ID
    std::vector<Hospital *> &getHospitals();          // Access all hospitals
    std::vector<std::pair<int, int>> getBeds() const; // HospitalID,BedID pairs
    void showBedStatus() const;                       // Display hospitalbedstatus
};

#endif
