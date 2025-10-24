#include "../include/greedy.h"
#include "../include/hospital.h"
#include <iostream>

using namespace std;

Hospital *GreedyAllocation::assignPatientToHospital(Patient &p, vector<Hospital *> &hospitalList)
{
    for (auto *h : hospitalList)
    {
        int bedID = h->assignBed(p);
        if (bedID != -1)
        {
            p.setHospitalID(h->getHospitalID());
            p.setBedID(bedID);
            p.setStatus("Admitted");
            return h;
        }
    }
    p.setStatus("Waiting");
    return nullptr;
}
