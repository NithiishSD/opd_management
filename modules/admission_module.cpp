#include "../include/admission_module.h"
#include <iostream>
using namespace std;

AdmissionModule::AdmissionModule(int totalBeds) : beds(totalBeds)
{
    // Initialize beds in the hash table
    for (int i = 0; i < totalBeds; i++)
        beds.allocateBed(i);
}

bool AdmissionModule::admitPatient(Patient &p)
{
    // Find first available bed
    for (int i = 0; i < totalBeds; i++)
    {
        if (beds.isAvailable(i))
        {
            beds.allocateBed(i); // Mark as occupied
            p.setAssignedBedID(i);
            cout << "[Admission] Patient " << p.getName()
                 << " admitted to bed " << i << "\n";
            return true;
        }
    }
    cout << "[Admission] No beds available for " << p.getName() << "\n";
    return false;
}

void AdmissionModule::showBedStatus() const
{
    cout << "[Admission] Current bed status:\n";
    beds.displayBeds();
}
void AdmissionModule::showBedStatus(int patientID) const
{
    cout << "\n[Admission] Checking bed for patient ID " << patientID << "...\n";
    // Here, you could later link to patient->bedID logic
    showBedStatus(); // fallback to general view for now
}
