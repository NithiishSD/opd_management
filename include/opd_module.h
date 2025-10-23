#ifndef OPD_MODULE_H
#define OPD_MODULE_H

#include "heap.h"
#include "patients.h"
#include <iostream>
using namespace std;

// OPD Module manages patients waiting in triage queue based on priority
class OPDModule
{
private:
    Heap triage; // Max-heap based on Patient.priority

public:
    OPDModule(int capacity = 100);

    void registerPatient(const Patient &p); // Add patient to queue
    Patient assignNextPatient();            // Serve next patient
    bool hasWaiting() const;                // Check if queue not empty
    void showQueue() const;                 // Display queue
};

#endif
