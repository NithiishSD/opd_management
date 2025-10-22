#ifndef OPD_MODULE_H
#define OPD_MODULE_H

#include "heap.h"
#include <iostream>
using namespace std;

class OPDModule
{
private:
    Heap queue; // max-heap based on Patient.priority

public:
    OPDModule();
    void registerPatient(int id, const string &name, int severity);
    bool hasWaitingPatients() const;
    Patient serveNextPatient(); // returns patient served (or default patient)
    void showQueue() const;
};

#endif
