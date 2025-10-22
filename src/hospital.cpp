#include "../include/hospital.h"
#include <iostream>
using namespace std;

// Default constructor
Hospital::Hospital() {
    hospitalID = 0;
    hospitalName = "";
    location = "";
    totalBeds = 0;
    availableBeds = 0;
}

// Parameterized constructor
Hospital::Hospital(int id, string name, string loc, int beds) {
    hospitalID = id;
    hospitalName = name;
    location = loc;
    totalBeds = beds;
    availableBeds = beds;

    // Initialize all beds as free
    for (int i = 1; i <= beds; i++) {
        bedStatus[i] = true; // true means available
    }
}

// ------------------- Basic Info -------------------
int Hospital::getHospitalID() const {
    return hospitalID;
}

string Hospital::getHospitalName() const {
    return hospitalName;
}

string Hospital::getLocation() const {
    return location;
}

// ------------------- Bed Management -------------------
bool Hospital::isBedAvailable() const {
    return availableBeds > 0;
}

int Hospital::getAvailableBeds() const {
    return availableBeds;
}

// Allocate a bed and return bed ID, -1 if none available
int Hospital::allocateBed() {
    for (auto &bed : bedStatus) {
        if (bed.second) { // if bed is free
            bed.second = false; // mark as occupied
            availableBeds--;
            return bed.first;
        }
    }
    return -1; // no free beds
}

// Release a bed by ID
void Hospital::releaseBed(int bedID) {
    if (bedStatus.find(bedID) != bedStatus.end() && !bedStatus[bedID]) {
        bedStatus[bedID] = true;
        availableBeds++;
    }
}

// ------------------- Patient Management -------------------
// Admit a patient
void Hospital::admitPatient(const Patient &patient) {
    int bedID = allocateBed();
    if (bedID != -1) {
        admittedPatients.push_back(patient);
        cout << "Patient " << patient.getName() << " admitted to " << hospitalName 
             << " at bed " << bedID << endl;
    } else {
        cout << "No beds available in " << hospitalName << " for patient " 
             << patient.getName() << endl;
    }
}

// Discharge a patient by ID
void Hospital::dischargePatient(int patientID) {
    for (int i = 0; i < admittedPatients.size(); i++) {
        if (admittedPatients[i].getPatientID() == patientID) {
            cout << "Patient " << admittedPatients[i].getName() << " discharged from " 
                 << hospitalName << endl;
            admittedPatients.erase(admittedPatients.begin() + i);

            // Release the first occupied bed (simple approach)
            for (auto &bed : bedStatus) {
                if (!bed.second) {
                    releaseBed(bed.first);
                    break;
                }
            }
            return;
        }
    }
    cout << "Patient ID " << patientID << " not found in " << hospitalName << endl;
}
