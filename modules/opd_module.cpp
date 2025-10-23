#include "../include/opd_module.h"
#include "../include/patients.h"
#include "../include/heap.h"
#include <iostream>
using namespace std;

// Constructor
OPDModule::OPDModule(int capacity) : triage(capacity) {}

// Register a patient into OPD queue
void OPDModule::registerPatient(const Patient &p)
{
    triage.insert(p);
    cout << "[OPD] Registered " << p.getName()
         << " (Priority " << p.getPriority() << ")\n";
}

// Assign next patient based on highest priority
Patient OPDModule::assignNextPatient()
{
    if (triage.isEmpty())
    {
        cout << "[OPD] No patients waiting\n";
        return Patient();
    }

    Patient p = triage.extractMax();
    cout << "[OPD] Assigning " << p.getName() << " to doctor\n";
    return p;
}

// Check if queue has waiting patients
bool OPDModule::hasWaiting() const
{
    return !triage.isEmpty();
}

// Display current queue
void OPDModule::showQueue() const
{
    if (triage.isEmpty())
    {
        cout << "⚠️  No patients currently in queue.\n";
        return;
    }

    cout << "\n====== 🩺 OPD Waiting Queue ======\n";
    triage.display(); // Calls Heap::display()
    cout << "=================================\n";
}
