#include "../include/greedy.h"
#include "../include/hospital.h"
#include <iostream>

using namespace std;

Hospital *GreedyAllocation::assignPatientToHospital(Patient &p, std::vector<Hospital *> &hospitalList)
{
    if (hospitalList.empty())
    {
        std::cout << "[GreedyAllocation] No hospitals provided for patient " << p.getName() << "\n";
        p.setStatus("Waiting");
        return nullptr;
    }

    for (auto *h : hospitalList)
    {
        int bedID = h->assignBed(p);
        if (bedID != -1)
        {

            p.setHospitalID(h->getHospitalID());
            p.setBedID(bedID);
            p.setStatus("Admitted");
            cout << "[GreedyAllocation] Assigned patient " << p.getName() << " to hospital " << h->getHospitalName() << " (Bed ID: " << bedID << ")\n";

            return h;
        }
        else
        {
            cout << "No beds available in hospital " << h->getHospitalName() << "\n";
        }
    }

    p.setStatus("Waiting");
    std::cout << "[GreedyAllocation] No beds available in any hospital for patient " << p.getName() << "\n";
    return nullptr;
}
