#include "../include/opd_module.h"
#include <iostream>

OPDModule::OPDModule(int capacity) : heap(capacity) {}

void OPDModule::registerPatient(const Patient &p)
{
    // compute priority automatically
    Patient temp = p;
    temp.computePriority(); // ensure priority is up-to-date
    heap.insert(temp);
    std::cout << "[OPD] Registered patient: " << p.getName()
              << " | Priority: " << temp.getPriority() << std::endl;
}

Patient OPDModule::assignNextPatient()
{
    if (!heap.isEmpty())
    {
        Patient p = heap.extractMax();
        std::cout << "[OPD] Assigning patient: " << p.getName() << std::endl;
        return p;
    }
    else
    {
        std::cout << "[OPD] No patients waiting\n";
        return Patient(); // default empty patient
    }
}

bool OPDModule::hasWaiting() const
{
    return !heap.isEmpty();
}

void OPDModule::showWaitingPatients() const
{
    std::cout << "\n[OPD] Waiting Patients (by priority):\n";
    std::vector<Patient> patients = heap.getHeapCopy();
    for (const auto &p : patients)
    {
        std::cout << "ID: " << p.getPatientID()
                  << " | Name: " << p.getName()
                  << " | Priority: " << p.getPriority() << std::endl;
    }
}
