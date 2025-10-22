#include "../include/opd_queue.h"
#include <iostream>
using namespace std;

// ------------------- Add Patient -------------------
void OPDQueue::addPatient(const Patient &p) {
    heap.insert(p);
    cout << "Patient " << p.getName() << " added to OPD queue." << endl;
}

// ------------------- Serve Next Patient -------------------
Patient OPDQueue::nextPatient() {
    if (heap.isEmpty()) {
        cout << "OPD queue is empty!" << endl;
        return Patient(); // return default patient
    }

    Patient topPatient = heap.extractMax(); // highest priority patient
    cout << "Serving patient " << topPatient.getName() << endl;
    return topPatient;
}

// ------------------- Check if Queue is Empty -------------------
bool OPDQueue::isEmpty() const {
    return heap.isEmpty();
}

// ------------------- Get Number of Patients in Queue -------------------
int OPDQueue::size() const {
    return heap.getSize();
}

// ------------------- Display Queue -------------------
void OPDQueue::display() const {
    cout << "OPD queue has " << heap.getSize() 
         << " patients (cannot display all directly)." << endl;
}
