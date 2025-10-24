#ifndef GREEDY_ALLOCATION_H
#define GREEDY_ALLOCATION_H

#include "hospital.h"
#include "patients.h"
#include <vector>

class GreedyAllocation
{
public:
    // Assign patient to the first hospital with available bed from the given list
    static Hospital *assignPatientToHospital(Patient &p, std::vector<Hospital *> &hospitalList);
};

#endif
