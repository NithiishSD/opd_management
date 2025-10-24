#ifndef OPD_MODULE_H
#define OPD_MODULE_H

#include "heap.h"
#include "patients.h"
#include <vector>
#include <iostream>

class OPDModule
{
private:
    Heap heap; // MaxHeap of patients

public:
    OPDModule(int capacity);

    void registerPatient(const Patient &p); // add patient to OPD
    Patient assignNextPatient();            // pop patient with highest priority
    bool hasWaiting() const;                // check if OPD has patients
    void showWaitingPatients() const;       // print all waiting patients
};

#endif
