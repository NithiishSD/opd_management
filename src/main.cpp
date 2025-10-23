#include "../include/patients.h"
#include "../include/heap.h"
#include "../include/hash_table.h"
#include "../include/opd_module.h"
#include "../include/admission_module.h"
#include "../include/discharge_module.h"
#include "../include/city_integartion_module.h"

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Calculate dynamic patient priority
int calculatePriority(int severity, int age)
{
    return severity * 2 + (age > 60 ? 3 : 0);
}

int main()
{
    cout << "=============================\n";
    cout << "   Hospital Management System\n";
    cout << "=============================\n";

    // Initialize modules
    OPDModule opd(50);

    // Admission module reads hospitals from CSV
    AdmissionModule admission("data/hospitals.csv", 20);
    DischargeModule discharge(admission.getBeds());

    // Get the list of hospitals from AdmissionModule
    vector<HospitalInfo> hospitalList = admission.getHospitals();

    // Initialize city integration module with the number of hospitals
    CityIntegrationModule city(hospitalList.size());

    // Add hospitals to the city module

    for (const auto &h : hospitalList)
    {
        city.addHospital(h.id, h.hospitalName, h.availableBeds, h.city);
    }
    int patientID = 100; // auto increment
    vector<Patient> admittedPatients;

    int choice;
    do
    {
        cout << "\n========= MAIN MENU =========\n";
        cout << "1. Register New Patient\n";
        cout << "2. Show OPD Waiting Queue\n";
        cout << "3. Show Hospital Bed Status\n";
        cout << "4. Show All Hospitals Status\n";
        cout << "5. Exit\n";
        cout << "=============================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string name, gender, disease;
            int age, severity;

            cin.ignore(); // clear input buffer
            cout << "\nEnter Patient Name: ";
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Gender: ";
            cin >> gender;
            cin.ignore();
            cout << "Enter Disease/Condition: ";
            getline(cin, disease);
            cout << "Enter Severity Level (1-10): ";
            cin >> severity;
            cin.ignore();

            int priority = calculatePriority(severity, age);
            Patient p(patientID++, name, age, gender, priority, disease);

            opd.registerPatient(p);

            // Automatically try to assign to hospital
            if (opd.hasWaiting())
            {
                Patient next = opd.assignNextPatient();
                bool admitted = admission.admitPatient(next);
                if (admitted)
                {
                    admittedPatients.push_back(next);
                    cout << "✅ Patient " << next.getName()
                         << " assigned to hospital " << next.getAssignedHospital()
                         << " (Bed #" << next.getAssignedBedID() << ")\n";
                }
                else
                {
                    cout << "⚠️ No beds available. Patient will wait in OPD queue.\n";
                }
            }
            break;
        }

        case 2:
            opd.showQueue();
            break;

        case 3:
            admission.showBedStatus();
            break;

        case 4:
            city.showHospitals();
            break;

        case 5:
            cout << "Exiting system...\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    cout << "\n=============================\n";
    cout << " Simulation Ended \n";
    cout << "=============================\n";

    return 0;
}
