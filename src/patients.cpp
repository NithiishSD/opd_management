#include "../include/patients.h"
#include <algorithm>
#include <iostream>
#include <cctype>

using namespace std;

// Constructor
Patient::Patient(int id, const string &name, int age, const string &gender,
                 const string &disease, const string &location)
{
    patientID = id;
    this->name = name;
    this->age = age;
    this->gender = gender;
    this->disease = disease;
    locationName = location;

    hospitalID = -1;
    bedID = -1;
    status = "Waiting";

    computePriority();
}

// Automatic priority computation
void Patient::computePriority()
{
    // Priority mapping: lower number = higher urgency
    unordered_map<string, int> diseaseSeverity = {
        {"heart attack", 1},
        {"stroke", 1},
        {"severe trauma", 1},
        {"cancer", 2},
        {"severe infection", 2},
        {"respiratory failure", 1},
        {"pneumonia", 2},
        {"diabetes complication", 3},
        {"fracture", 3},
        {"flu", 4},
        {"mild infection", 4},
        {"checkup", 5}};

    int basePriority = 5; // default if disease not listed
    string d = disease;
    transform(d.begin(), d.end(), d.begin(), ::tolower);

    for (auto &pair : diseaseSeverity)
    {
        if (d.find(pair.first) != string::npos)
        {
            basePriority = pair.second;
            break;
        }
    }

    // Age adjustment: elderly (>65) or very young (<5) increase priority
    if (age > 65 || age < 5)
        basePriority = max(1, basePriority - 1);

    priority = basePriority;
}

// Getters
int Patient::getPatientID() const { return patientID; }
string Patient::getName() const { return name; }
int Patient::getAge() const { return age; }
string Patient::getGender() const { return gender; }
string Patient::getDisease() const { return disease; }
string Patient::getLocationName() const { return locationName; }
int Patient::getPriority() const { return priority; }
int Patient::getHospitalID() const { return hospitalID; }
int Patient::getBedID() const { return bedID; }
string Patient::getStatus() const { return status; }

// Setters
void Patient::setHospitalID(int id) { hospitalID = id; }
void Patient::setBedID(int id) { bedID = id; }
void Patient::setStatus(const string &s) { status = s; }
