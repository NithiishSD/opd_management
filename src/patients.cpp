#include "../include/patients.h"
#include <iostream>
#include <ctime>
using namespace std;

// ------------------- Default Constructor -------------------
Patient::Patient() {
    patientID = 0;
    name = "";
    age = 0;
    gender = "";
    priority = 0;
    arrivalTime = time(nullptr); // current time
    disease = "";
    assignedHospital = "";
    assignedBedID = -1;
}

// ------------------- Parameterized Constructor -------------------
Patient::Patient(int id, string n, int a, string g, int p, string d) {
    patientID = id;
    name = n;
    age = a;
    gender = g;
    priority = p;
    disease = d;
    arrivalTime = time(nullptr); // current time
    assignedHospital = "";
    assignedBedID = -1;
}

// ------------------- Getters -------------------
int Patient::getPatientID() const { return patientID; }
string Patient::getName() const { return name; }
int Patient::getAge() const { return age; }
string Patient::getGender() const { return gender; }
int Patient::getPriority() const { return priority; }
time_t Patient::getArrivalTime() const { return arrivalTime; }
string Patient::getDisease() const { return disease; }
string Patient::getAssignedHospital() const { return assignedHospital; }
int Patient::getAssignedBedID() const { return assignedBedID; }

// ------------------- Setters -------------------
void Patient::setAssignedHospital(const string &hospital) {
    assignedHospital = hospital;
}

void Patient::setAssignedBedID(int bedID) {
    assignedBedID = bedID;
}
