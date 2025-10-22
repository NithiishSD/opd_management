#include "../include/heap.h"
#include <iostream>
using namespace std;

class OPDModule
{
    Heap triage;

public:
    OPDModule(int capacity = 100) : triage(capacity) {}

    void registerPatient(const Patient &p)
    {
        triage.insert(p);
        cout << "[OPD] Registered " << p.getName()
             << " (Priority " << p.getPriority() << ")\n";
    }

    Patient assignNextPatient()
    {
        if (triage.isEmpty())
        {
            cout << "[OPD] No patients waiting\n";
            return Patient();
        }
        Patient p = triage.extractMax();
        cout << "[OPD] Assigning " << p.getName() << " to doctor\n";
        return p;
    }

    bool hasWaiting() const { return !triage.isEmpty(); }
};
