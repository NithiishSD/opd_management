#include "../include/patients.h"
#include "../include/heap.h"
#include "../include/hash_table.h"
#include "../modules/opd_module.cpp"
#include "../modules/admission_module.cpp"
#include "../modules/discharge_module.cpp"
#include "../modules/city_integration_module.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to read patients from CSV
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
    getline(file, line); // skip header
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, age, gender, priority, disease;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, gender, ',');
        getline(ss, priority, ',');
        getline(ss, disease, ',');
        Patient p(stoi(id), name, stoi(age), gender, stoi(priority), disease);
        patients.push_back(p);
    }
    return patients;
}

int main()
{
    cout << "=== Hospital Management System ===\n";

    // Initialize modules
    OPDModule opd(10);
    AdmissionModule admission(2);
    DischargeModule discharge(admission.getBeds());

    CityIntegrationModule city(3);
    city.addHospital(0, "City Hospital A", 2);
    city.addHospital(1, "City Hospital B", 1);
    city.addHospital(2, "City Hospital C", 3);

    city.setDistance(0, 1, 5);
    city.setDistance(0, 2, 10);
    city.setDistance(1, 2, 2);

    // Read patients from CSV
    vector<Patient> patients = readPatientsFromCSV("../data/patients.csv");
    for (const auto &p : patients)
        opd.registerPatient(p);

    int choice;
    do
    {
        cout << "\n=== Menu ===\n";
        cout << "1. Assign next patient from OPD to hospital\n";
        cout << "2. Discharge patient by ID\n";
        cout << "3. Show hospital bed status\n";
        cout << "4. Show city hospitals status\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            if (opd.hasWaiting())
            {
                Patient p = opd.assignNextPatient();
                bool admitted = admission.admitPatient(p);
                if (!admitted)
                {
                    cout << "[Main] Hospital full. Searching city hospitals for " << p.getName() << "\n";
                    city.findNearestHospitalWithBed(p);
                }
            }
            else
            {
                cout << "[Main] No patients waiting in OPD\n";
            }
            break;
        }
        case 2:
        {
            int pid;
            cout << "Enter patient ID to discharge: ";
            cin >> pid;
            // Find patient object
            auto it = find_if(patients.begin(), patients.end(), [pid](Patient &p)
                              { return p.getPatientID() == pid; });
            if (it != patients.end())
                discharge.dischargePatient(*it);
            else
                cout << "[Main] Patient ID not found\n";
            break;
        }
        case 3:
            admission.showBedStatus();
            break;
        case 4:
            city.showHospitals();
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 5);

    cout << "\n=== Simulation Completed ✅ ===\n";
    return 0;
}
