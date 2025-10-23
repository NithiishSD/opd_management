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

// Function to calculate patient priority dynamically
int calculatePriority(int severity, int age)
{
    // You can adjust weights here — higher severity and age get higher priority
    return severity * 2 + (age > 60 ? 3 : 0);
}

int main()
{
    cout << "=============================\n";
    cout << "   Hospital Management System\n";
    cout << "=============================\n";

    // Initialize modules
    OPDModule opd(50);
    AdmissionModule admission(5);
    DischargeModule discharge(admission.getBeds());

    // Create city hospital graph (3 hospitals)
    CityIntegrationModule city(3);
    city.addHospital(0, "City Hospital A", 2);
    city.addHospital(1, "City Hospital B", 1);
    city.addHospital(2, "City Hospital C", 3);

    city.setDistance(0, 1, 5);
    city.setDistance(0, 2, 10);
    city.setDistance(1, 2, 2);

    int choice;
    int patientID = 100; // auto increment
    vector<Patient> admittedPatients;

    do
    {
        cout << "\n========= MAIN MENU =========\n";
        cout << "1. Register New Patient in OPD\n";
        cout << "2. Assign Patient to Hospital\n";
        cout << "3. Discharge Patient\n";
        cout << "4. Show OPD Waiting Queue\n";
        cout << "5. Show Hospital Bed Status\n";
        cout << "6. Show City Hospitals Status\n";
        cout << "7. Exit\n";
        cout << "=============================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string name, gender, disease;
            int age, severity;

            cout << "\nEnter Patient Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Gender: ";
            cin >> gender;
            cout << "Enter Disease/Condition: ";
            cin.ignore();
            getline(cin, disease);
            cout << "Enter Severity Level (1-10): ";
            cin >> severity;

            int priority = calculatePriority(severity, age);
            Patient p(patientID++, name, age, gender, priority, disease);
            opd.registerPatient(p);
            cout << " Patient " << p.getName() << " registered with priority " << p.getPriority() << endl;
            break;
        }

        case 2:
        {
            if (opd.hasWaiting())
            {
                Patient next = opd.assignNextPatient();
                cout << "Assigning " << next.getName() << " to hospital...\n";

                bool admitted = admission.admitPatient(next);
                if (admitted)
                {
                    admittedPatients.push_back(next);
                    cout << "🏥 " << next.getName() << " successfully admitted locally.\n";
                }
                else
                {
                    cout << " Local hospital full. Finding nearest hospital...\n";
                    city.findNearestHospitalWithBed(next);
                }
            }
            else
            {
                cout << "No patients waiting in OPD.\n";
            }
            break;
        }

        case 3:
        {
            if (admittedPatients.empty())
            {
                cout << " No patients currently admitted.\n";
                break;
            }

            cout << "Enter Patient ID to discharge: ";
            int pid;
            cin >> pid;

            auto it = find_if(admittedPatients.begin(), admittedPatients.end(),
                              [pid](Patient &p)
                              { return p.getPatientID() == pid; });

            if (it != admittedPatients.end())
            {
                discharge.dischargePatient(*it);
                admission.showBedStatus((*it).getPatientID());
                admittedPatients.erase(it);
                cout << " Patient discharged successfully.\n";
            }
            else
            {
                cout << " Patient ID not found in current admissions.\n";
            }
            break;
        }

        case 4:
            opd.showQueue();
            break;

        case 5:
            admission.showBedStatus();
            break;

        case 6:
            city.showHospitals();
            break;

        case 7:
            cout << "Exiting system\n";
            break;

        default:
            cout << "Invalid option. Try again.\n";
        }

    } while (choice != 7);

    cout << "\n=============================\n";
    cout << " Simulation Ended \n";
    cout << "=============================\n";
    return 0;
}
