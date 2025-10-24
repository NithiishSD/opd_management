#ifndef OPD_QUEUE_H
#define OPD_QUEUE_H

#include "heap.h"
#include "patients.h"

class OPDQueue
{
private:
    Heap heap;

public:
    OPDQueue(int capacity) : heap(capacity) {}
    void addPatient(const Patient &p);
    Patient nextPatient();
    bool isEmpty() const;
    int size() const;
    void display() const;
};

#endif
