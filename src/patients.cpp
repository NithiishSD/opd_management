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
    // Priority mapping:
    unordered_map<string, int> diseaseSeverity = {
        {"heart attack", 5},
        {"stroke", 5},
        {"severe trauma", 5},
        {"cancer", 4},
        {"severe infection", 4},
        {"respiratory failure", 5},
        {"pneumonia", 4},
        {"diabetes complication", 3},
        {"fracture", 3},
        {"flu", 2},
        {"mild infection", 2},
        {"checkup", 1}};

    int basePriority = 2; // default if disease not listed
    string d = disease;
    for (size_t i = 0; i < d.size(); ++i)
        d[i] = static_cast<char>(tolower(static_cast<int>(static_cast<unsigned char>(d[i]))));

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
        basePriority = max(5, basePriority + 1);

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
