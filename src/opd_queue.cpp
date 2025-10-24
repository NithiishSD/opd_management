#include "../include/opd_module.h"
#include "../include/patients.h"
#include <iostream>
#include <vector>

using namespace std;

OPDModule::OPDModule(int capacity)
{
    this->capacity = capacity;
}

void OPDModule::registerPatient(const Patient &p)
{
    if (patientHeap.size() >= capacity)
    {
        cout << "[OPDModule] OPD queue full! Cannot add patient " << p.getName() << "\n";
        return;
    }
    patientHeap.insert(p); // Insert into custom max-heap
    cout << "[OPDModule] Patient " << p.getName() << " added to OPD queue.\n";
}

bool OPDModule::hasWaiting() const
{
    return patientHeap.size() > 0;
}

Patient OPDModule::assignNextPatient()
{
    if (patientHeap.size() == 0)
    {
        throw runtime_error("[OPDModule] No patients in OPD queue!");
    }
    return patientHeap.extractMax(); // Extract patient with highest priority
}

void OPDModule::showQueue() const
{
    vector<Patient> patients = patientHeap.getAllElements(); // Get all elements for display
    if (patients.empty())
    {
        cout << "[OPDModule] No patients waiting in OPD.\n";
        return;
    }

    cout << "PatientID\tName\tPriority\tLocation\n";
    for (const auto &p : patients)
    {
        cout << p.getPatientID() << "\t" << p.getName() << "\t"
             << p.getPriority() << "\t" << p.getLocationName() << "\n";
    }
}
