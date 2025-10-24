#ifndef HEAP_H
#define HEAP_H

#include "patients.h"
#include <vector>
#include <stdexcept>

class Heap
{
private:
    std::vector<Patient> heap;
    int maxCapacity = 0; // 0 means unlimited

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    Heap() = default;
    Heap(int capacity) : maxCapacity(capacity) {}

    void insert(const Patient &p);            // Add patient to heap
    Patient extractMax();                     // Remove and return highest priority patient
    Patient peek() const;                     // View top patient
    int size() const;                         // Heap size
    bool isEmpty() const;                     // Check if heap is empty
    std::vector<Patient> getHeapCopy() const; // Return all patients
};

#endif
