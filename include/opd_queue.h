#ifndef opd_queue_h
#define opd_queue_h

#include <queue>
#include <vector>
#include "patients.h"
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
    priority_queue<Patient, vector<Patient>, ComparePriority> pq;

public:
    void addPatient(const Patient &p);
    Patient nextPatient();
    bool isEmpty() const;
    int size() const;
};

#endif
