#ifndef DISCHARGE_MODULE_H
#define DISCHARGE_MODULE_H

#include "../include/patients.h"
#include "../include/hash_table.h"
#include <iostream>
using namespace std;

class DischargeModule
{
    HashTable &beds;

public:
    DischargeModule(HashTable &bedsRef);

    void dischargePatient(Patient &p);
};

#endif
