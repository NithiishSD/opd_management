#ifndef DISCHARGE_MODULE_H
#define DISCHARGE_MODULE_H

#include "patients.h"
#include "hospital.h"
#include <vector>
#include <iostream>

class DischargeModule
{
private:
    std::vector<Hospital *> &hospitals; // reference to hospital list

public:
    DischargeModule(std::vector<Hospital *> &hospList);

    void dischargePatient(Patient &p); // discharge a patient and free bed
};

#endif
