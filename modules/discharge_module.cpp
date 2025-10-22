#include "../include/discharge_module.h"
#include <iostream>
using namespace std;

DischargeModule::DischargeModule(HashTable &bedsRef) : beds(bedsRef) {}

void DischargeModule::dischargePatient(Patient &p)
{
    int bedID = p.getAssignedBedID();
    if (bedID == -1)
    {
        cout << "[Discharge] Patient " << p.getName() << " is not assigned a bed.\n";
        return;
    }

    beds.freeBed(bedID);
    cout << "[Discharge] Patient " << p.getName() << " discharged from bed " << bedID << "\n";

    p.setAssignedBedID(-1);
}
