#include "../include/utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <cctype>

using namespace std;

// ================= String Utilities =================
string trim(const string &str)
{
    string s = str;
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch)
                               { return !isspace(ch); }));
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                    { return !isspace(ch); })
                .base(),
            s.end());
    return s;
}

bool isNumber(const string &s)
{
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

vector<Patient> readPatientsFromCSV(const string &filename)
{
    vector<Patient> patients;
    ifstream file(filename);
    if (!file)
    {
        cout << "Error: Could not open " << filename << endl;
        return patients;
    }

    string line;
    getline(file, line);

    while (getline(file, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string id, name, age, gender, disease, location;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, gender, ',');
        getline(ss, disease, ',');
        getline(ss, location, ',');

        id = trim(id);
        age = trim(age);

        if (id.empty() || age.empty() || !isNumber(id) || !isNumber(age))
        {
            cout << "Skipping invalid row: " << line << endl;
            continue;
        }

        Patient p(stoi(id), name, stoi(age), gender, disease, location);
        patients.push_back(p);
    }

    return patients;
}

vector<Hospital> readHospitalsFromCSV(const string &filename)
{
    vector<Hospital> hospitals;
    ifstream file(filename);
    if (!file)
    {
        cout << "Error: Could not open " << filename << endl;
        return hospitals;
    }

    string line;
    getline(file, line);

    while (getline(file, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string id, name, location, bedCount;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, location, ',');
        getline(ss, bedCount, ',');

        id = trim(id);
        bedCount = trim(bedCount);

        if (id.empty() || bedCount.empty() || !isNumber(id) || !isNumber(bedCount))
        {
            cout << "Skipping invalid row: " << line << endl;
            continue;
        }

        Hospital h(stoi(id), name, location, stoi(bedCount));
        hospitals.push_back(h);
    }

    return hospitals;
}
void savePatientToCSV(const char *filename, const Patient &patient)
{

    vector<Patient> patients = readPatientsFromCSV(filename);

    bool patientExists = false;
    for (auto &p : patients)
    {
        if (p.getPatientID() == patient.getPatientID())
        {

            p = patient;
            patientExists = true;
            break;
        }
    }

    // If patient doesn't exist, append it
    if (!patientExists)
    {
        patients.push_back(patient);
    }

    // Write all patients back to CSV
    ofstream file(filename);
    if (!file)
    {
        cout << "Error: Could not open " << filename << " for writing" << endl;
        return;
    }

    // Write header
    file << "id,name,age,gender,disease,location\n";

    // Write patient data
    for (const auto &p : patients)
    {
        file << p.getPatientID() << ","
             << p.getName() << ","
             << p.getAge() << ","
             << p.getGender() << ","
             << p.getDisease() << ","
             << p.getLocationName() << "\n";
    }

    file.close();
}

Patient *findPatientByID(vector<Patient> &patients, int patientID)
{
    for (auto &p : patients)
    {
        if (p.getPatientID() == patientID)
            return &p;
    }
    return nullptr;
}

Hospital *findHospitalByID(vector<Hospital> &hospitals, int hospitalID)
{
    for (auto &h : hospitals)
    {
        if (h.getHospitalID() == hospitalID)
            return &h;
    }
    return nullptr;
}
