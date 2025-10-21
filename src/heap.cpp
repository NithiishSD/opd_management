#include "heap.h"
#include <iostream>

using namespace std;

int Heap::parent(int i) { return (i - 1) / 2; }
int Heap::left(int i) { return 2 * i + 1; }
int Heap::right(int i) { return 2 * i + 2; }

void Heap::heapifyUp(int i)
{
    while (i != 0 && arr[parent(i)].getPriority() < arr[i].getPriority())
    {
        swap(arr[i], arr[parent(i)]);
        i = parent(i);
    }
}

void Heap::heapifyDown(int i)
{
    int largest = i;
    int l = left(i), r = right(i);

    if (l < size && arr[l].getPriority() > arr[largest].getPriority())
        largest = l;
    if (r < size && arr[r].getPriority() > arr[largest].getPriority())
        largest = r;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapifyDown(largest);
    }
}

// Public member functions
Heap::Heap(int capacity)
{
    this->capacity = capacity;
    size = 0;
    arr = new Patient[capacity];
}

Heap::~Heap()
{
    delete[] arr;
}

bool Heap::isEmpty() const { return size == 0; }
bool Heap::isFull() const { return size == capacity; }
int Heap::getSize() const { return size; }

void Heap::insert(const Patient &p)
{
    if (isFull())
    {
        cout << "Heap overflow!\n";
        return;
    }
    arr[size] = p;
    heapifyUp(size);
    size++;
}

Patient Heap::extractMax()
{
    if (isEmpty())
    {
        cout << "Heap underflow!\n";
        return Patient();
    }
    Patient root = arr[0];
    arr[0] = arr[size - 1];
    size--;
    heapifyDown(0);
    return root;
}

void Heap::display() const
{
    cout << "\n--- OPD Priority Queue ---\n";
    for (int i = 0; i < size; i++)
    {
        cout << "[" << arr[i].getPatientID() << "] "
             << arr[i].getName() << " (Priority: " << arr[i].getPriority() << ")\n";
    }
}
