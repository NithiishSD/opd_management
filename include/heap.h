#ifndef HEAP_H
#define HEAP_H

#include "patients.h"
#include <vector>
#include <stdexcept>

class Heap
{
private:
    std::vector<Patient> heap;
    int maxCapacity = 0;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    Heap() = default;
    Heap(int capacity) : maxCapacity(capacity) {}

    void insert(const Patient &p);
    Patient extractMax();
    Patient peek() const;
    int size() const;
    bool isEmpty() const;
    std::vector<Patient> getHeapCopy() const;
};

#endif
