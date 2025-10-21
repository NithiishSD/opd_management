#ifndef hospital_h
#define hospital_h

#include <string>
#include <vector>
#include <unordered_map>
#include "patients.h"
using namespace std;

class Hospital
{
private:
    int hospitalID;
    string hospitalName;
    string location;
    int totalBeds;
    int availableBeds;

public:
    unordered_map<int, bool> bedStatus;
    vector<Patient> admittedPatients;

    Hospital();
    Hospital(int id, string name, string loc, int beds);

    // Basic info
    int getHospitalID() const;
    string getHospitalName() const;
    string getLocation() const;

    // Bed Management
    bool isBedAvailable() const;
    int getAvailableBeds() const;
    int allocateBed();
    void releaseBed(int bedID);

    // Patient Management
    void admitPatient(const Patient &patient);
    void dischargePatient(int patientID);
};

#endif
