#ifndef OPD_MODULE_H
#define OPD_MODULE_H

#include "heap.h"
#include "patients.h"
#include <vector>
#include <iostream>

class OPDModule
{
private:
    Heap heap;

public:
    OPDModule(int capacity);

    void registerPatient(const Patient &p);
    Patient assignNextPatient();
    bool hasWaiting() const;
    void showWaitingPatients() const;
};

#endif
