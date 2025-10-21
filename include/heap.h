#ifndef HEAP_H
#define HEAP_H

#include "patients.h"

class Heap
{
private:
    Patient *arr;
    int capacity;
    int size;

    int parent(int i);
    int left(int i);
    int right(int i);
    void heapifyUp(int i);
    void heapifyDown(int i);

public:
    Heap(int capacity = 100);
    ~Heap();

    bool isEmpty() const;
    bool isFull() const;
    int getSize() const;

    void insert(const Patient &p);
    Patient extractMax();
    void display() const;
};

#endif
