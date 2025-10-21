#include "hash_table.h"
#include <iostream>
using namespace std;

// Bed constructor
Bed::Bed() : bedID(-1), isOccupied(false), isDeleted(false) {}

// Private hash function
int HashTable::hashFunc(int key) const
{
    return key % capacity;
}

// Public member functions
HashTable::HashTable(int capacity)
{
    this->capacity = capacity;
    size = 0;
    table = new Bed[capacity];
}

HashTable::~HashTable()
{
    delete[] table;
}

bool HashTable::isFull() const
{
    return size == capacity;
}

void HashTable::allocateBed(int bedID)
{
    if (isFull())
    {
        cout << "Hash table full! Cannot allocate.\n";
        return;
    }

    int idx = hashFunc(bedID);
    int startIdx = idx;

    while (table[idx].isOccupied && !table[idx].isDeleted)
    {
        idx = (idx + 1) % capacity;
        if (idx == startIdx)
        {
            cout << "No empty slot available!\n";
            return;
        }
    }

    table[idx].bedID = bedID;
    table[idx].isOccupied = true;
    table[idx].isDeleted = false;
    size++;
}

void HashTable::freeBed(int bedID)
{
    int idx = hashFunc(bedID);
    int startIdx = idx;

    while (table[idx].bedID != -1)
    {
        if (table[idx].bedID == bedID && table[idx].isOccupied)
        {
            table[idx].isOccupied = false;
            table[idx].isDeleted = true;
            cout << "Bed " << bedID << " released.\n";
            size--;
            return;
        }
        idx = (idx + 1) % capacity;
        if (idx == startIdx)
            break;
    }
    cout << "Bed not found!\n";
}

bool HashTable::isAvailable(int bedID) const
{
    int idx = hashFunc(bedID);
    int startIdx = idx;

    while (table[idx].bedID != -1)
    {
        if (table[idx].bedID == bedID && table[idx].isOccupied)
            return false;
        idx = (idx + 1) % capacity;
        if (idx == startIdx)
            break;
    }
    return true;
}

void HashTable::displayBeds() const
{
    cout << "\n--- Bed Status ---\n";
    for (int i = 0; i < capacity; i++)
    {
        if (table[i].isOccupied)
            cout << "Bed " << table[i].bedID << " → OCCUPIED\n";
        else if (table[i].isDeleted)
            cout << "Bed " << table[i].bedID << " → FREED\n";
        else
            cout << "Slot " << i << " → EMPTY\n";
    }
}
