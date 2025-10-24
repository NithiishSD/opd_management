#include "../include/patients.h"
#include "../include/hospital.h"
#include "../include/opd_module.h"
#include "../include/admission_module.h"
#include "../include/discharge_module.h"
#include "../include/city_integration_module.h"
#include "../include/utils.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cout << "=== Hospital Management System ===\n";

    // ================= Load Hospitals =================
    vector<Hospital> hospitalList = readHospitalsFromCSV("data/hospitals.csv");
    vector<Hospital *> hospitalPtrs;
    for (auto &h : hospitalList)
    {
        hospitalPtrs.push_back(&h);
    }

    // ================= Load Patients =================
    vector<Patient> patients = readPatientsFromCSV("data/patients.csv");

    // ================= Initialize Modules =================
    OPDModule opd(1000); // OPD max capacity
    AdmissionModule admission(hospitalList);
    DischargeModule discharge(hospitalList);

    CityIntegrationModule city(hospitalList);

    // ================= Register Patients in OPD =================
    for (auto &p : patients)
    {
        opd.registerPatient(p);
    }

    // ================= Patient ID Counter =================
    int patientCounter = 1;
    for (const auto &p : patients)
    {
        if (p.getPatientID() >= patientCounter)
        {
            patientCounter = p.getPatientID() + 1;
        }
    }

    int choice;
    do
    {
        cout << "\n=== Menu ===\n";
        cout << "1. Add New Patient\n";
        cout << "2. Admit next patient from OPD\n";
        cout << "3. Discharge patient by ID\n";
        cout << "4. Show OPD waiting patients\n";
        cout << "5. Show hospital bed status\n";
        cout << "6. Show hospitals overview\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline from input buffer

        switch (choice)
        {
        case 1:
        {
            string name, gender, disease, location;
            int age;

            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            cin.ignore();
            cout << "Enter Gender: ";
            getline(cin, gender);
            cout << "Enter Disease: ";
            getline(cin, disease);
            cout << "Enter Patient Location: ";
            getline(cin, location);

            // Create new patient
            Patient p(patientCounter++, name, age, gender, disease, location);
            p.computePriority();   // Compute priority based on disease and age
            patients.push_back(p); // Add to patients vector

            // Attempt to admit the patient
            bool admitted = admission.admitPatient(p);
            if (!admitted)
            {
                cout << "[Main] Hospital full. Searching nearest hospital for patient " << p.getName() << endl;
                bool assigned = city.assignPatientToNearestHospital(p);
                if (!assigned)
                {
                    cout << "[Main] All hospitals full. Adding patient to OPD queue.\n";
                    opd.registerPatient(p);
                }
            }
            else
            {
                cout << "[Main] Patient " << p.getName() << " admitted successfully in the hospital<<.\n";
            }

            // Save patient to CSV
            savePatientToCSV("data/patients.csv", p);
            break;
        }

        case 2:
        {
            if (opd.hasWaiting())
            {
                Patient p = opd.assignNextPatient();
                bool admitted = admission.admitPatient(p);
                if (!admitted)
                {
                    cout << "[Main] Hospital full. Searching nearest hospital for patient " << p.getName() << endl;
                    city.assignPatientToNearestHospital(p);
                }
            }
            else
            {
                cout << "[Main] No patients waiting in OPD\n";
            }
            break;
        }

        case 3:
        {
            int pid;
            cout << "Enter patient ID to discharge: ";
            cin >> pid;
            cin.ignore();
            Patient *p = findPatientByID(patients, pid);
            if (p)
            {
                discharge.dischargePatient(*p);
                savePatientToCSV("data/patients.csv", *p); // Update patient status in CSV
            }
            else
            {
                cout << "[Main] Patient ID not found\n";
            }
            break;
        }

        case 4:
            opd.showWaitingPatients();
            break;

        case 5:
            for (auto *h : hospitalPtrs)
            {
                cout << "\nHospital: " << h->getHospitalName() << " | Location: " << h->getLocationName() << endl;
                vector<int> occupiedBeds = h->getOccupiedBeds();
                if (occupiedBeds.empty())
                {
                    cout << "No beds occupied.\n";
                }
                else
                {
                    cout << "Occupied Beds: ";
                    for (int bedID : occupiedBeds)
                        cout << bedID << " ";
                    cout << endl;
                }
            }
            break;

        case 6:
            cout << "\n=== Hospitals Overview ===\n";
            for (auto *h : hospitalPtrs)
            {
                cout << "Hospital: " << h->getHospitalName()
                     << " | Location: " << h->getLocationName()
                     << " | Total Beds: " << h->getOccupiedBeds().size() << "/"
                     << h->getTotalBeds() << endl;
            }
            break;

        case 7:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 7);

    cout << "\n=== Simulation Completed ===\n";
    return 0;
}
