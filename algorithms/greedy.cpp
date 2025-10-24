#include "../include/greedy.h"
#include <iostream>

using namespace std;

// Greedy allocation: assign patient to first hospital with free bed
bool GreedyAllocation::assignPatientToHospital(Patient &p, vector<Hospital *> &hospitalList)
{
    for (auto *h : hospitalList)
    {
        int bedID = h->assignBed(p);
        if (bedID != -1)
        {
            p.setHospitalID(h->getHospitalID());
            p.setBedID(bedID);
            p.setStatus("Admitted");
            return true;
        }
    }
    p.setStatus("Waiting");
    return false;
}
