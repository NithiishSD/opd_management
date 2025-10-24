#include "../include/heap.h"
#include <iostream>
#include <algorithm>

void Heap::heapifyUp(int index)
{
    if (index == 0)
        return;
    int parent = (index - 1) / 2;
    if (heap[index].getPriority() > heap[parent].getPriority())
    {
        std::swap(heap[index], heap[parent]);
        heapifyUp(parent);
    }
}

void Heap::heapifyDown(int index)
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;

    if (left < heap.size() && heap[left].getPriority() > heap[largest].getPriority())
        largest = left;
    if (right < heap.size() && heap[right].getPriority() > heap[largest].getPriority())
        largest = right;

    if (largest != index)
    {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}

void Heap::insert(const Patient &p)
{
    if (maxCapacity > 0 && heap.size() >= maxCapacity)
    {
        std::cout << "[Heap] Heap full. Cannot insert patient " << p.getName() << "\n";
        return;
    }
    heap.push_back(p);
    heapifyUp(heap.size() - 1);
}

Patient Heap::extractMax()
{
    if (heap.empty())
        throw std::runtime_error("Heap is empty");

    Patient top = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty())
        heapifyDown(0);
    return top;
}

Patient Heap::peek() const
{
    if (heap.empty())
        throw std::runtime_error("Heap is empty");
    return heap[0];
}

int Heap::size() const
{
    return heap.size();
}

bool Heap::isEmpty() const
{
    return heap.empty();
}

std::vector<Patient> Heap::getHeapCopy() const
{
    return heap;
}
