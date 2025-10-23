#include "../include/patients.h"
#include <ctime>

// Default constructor
Patient::Patient()
{
    patientID = -1;
    name = "";
    age = 0;
    gender = "";
    priority = 0;
    disease = "";
    assignedHospital = "";
    assignedBedID = -1;
    arrivalTime = time(nullptr);
    location = "";
}

// Constructor without location
Patient::Patient(int id, string n, int a, string g, int p, string d)
{
    patientID = id;
    name = n;
    age = a;
    gender = g;
    priority = p;
    disease = d;
    assignedHospital = "";
    assignedBedID = -1;
    arrivalTime = time(nullptr);
    location = "";
}

// Constructor with location
Patient::Patient(int id, string n, int a, string g, int p, string d, string loc)
{
    patientID = id;
    name = n;
    age = a;
    gender = g;
    priority = p;
    disease = d;
    assignedHospital = "";
    assignedBedID = -1;
    arrivalTime = time(nullptr);
    location = loc;
}

// Getters
int Patient::getPatientID() const { return patientID; }
string Patient::getName() const { return name; }
int Patient::getAge() const { return age; }
string Patient::getGender() const { return gender; }
int Patient::getPriority() const { return priority; }
time_t Patient::getArrivalTime() const { return arrivalTime; }
string Patient::getDisease() const { return disease; }
string Patient::getAssignedHospital() const { return assignedHospital; }
int Patient::getAssignedBedID() const { return assignedBedID; }
string Patient::getLocation() const { return location; }

// Setters
void Patient::setAssignedHospital(const string &hospital)
{
    assignedHospital = hospital;
}

void Patient::setAssignedBedID(int bedID)
{
    assignedBedID = bedID;
}

void Patient::setLocation(const string &loc)
{
    location = loc;
}
