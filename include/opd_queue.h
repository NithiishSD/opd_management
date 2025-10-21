#ifndef opd_queue_h
#define opd_queue_h

#include <queue>
#include <vector>
#include "patients.h"
#include "heap.h"
using namespace std;

struct ComparePriority
{
    bool operator()(const Patient &a, const Patient &b)
    {
        return a.getPriority() > b.getPriority(); //
    }
};

class OPDQueue
{
private:
    Heap heap;

public:
    OPDQueue(int capacity = 100) : heap(capacity) {}
    void addPatient(const Patient &p);
    Patient nextPatient();
    bool isEmpty() const;
    int size() const;
    void display() const;
};

#endif
