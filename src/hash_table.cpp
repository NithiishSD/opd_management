#include "../include/hash_table.h"
#include <iostream>
using namespace std;

HashTable::HashTable(int cap) : capacity(cap), bedsOccupied(cap, false) {}

// Check if all beds are occupied
bool HashTable::isFull() const
{
    return getOccupiedBeds() >= capacity;
}

// Allocate first free bed to a patientID
bool HashTable::allocateBed(int patientID, int &bedID)
{
    if (isFull())
        return false;
    for (int i = 0; i < capacity; ++i)
    {
        if (!bedsOccupied[i])
        {
            bedsOccupied[i] = true;
            bedID = i + 1;
            patientBedMap[patientID] = bedID;
            return true;
        }
    }
    return false;
}

// Allocate first free bed, return bedID via reference (without patientID)
// bool HashTable::allocateBed(int &bedID)
// {
//     if (isFull())
//         return false;
//     for (int i = 0; i < capacity; ++i)
//     {
//         if (!bedsOccupied[i])
//         {
//             bedsOccupied[i] = true;
//             bedID = i + 1;
//             return true;
//         }
//     }
//     return false;
// }

// Free bed assigned to patientID
void HashTable::freeBed(int patientID)
{
    auto it = patientBedMap.find(patientID);
    if (it != patientBedMap.end())
    {
        int bedID = it->second;
        if (bedID >= 1 && bedID <= capacity)
            bedsOccupied[bedID - 1] = false;
        patientBedMap.erase(it);
    }
}

// Check if a bed is available
bool HashTable::isAvailable(int bedID) const
{
    if (bedID < 1 || bedID > capacity)
        return false;
    return !bedsOccupied[bedID - 1];
}

// Display all beds
void HashTable::displayBeds() const
{
    cout << "Bed Status:\n";
    for (int i = 0; i < capacity; ++i)
    {
        cout << "Bed " << i + 1 << ": "
             << (bedsOccupied[i] ? "Occupied" : "Free") << "\n";
    }
}

// Getters
int HashTable::getTotalBeds() const { return capacity; }

int HashTable::getOccupiedBeds() const
{
    int count = 0;
    for (bool occupied : bedsOccupied)
        if (occupied)
            count++;
    return count;
}
bool HashTable::allocateBed(int bedID)
{
    if (bedID <= 0 || bedID > static_cast<int>(bedsOccupied.size()) || bedsOccupied[bedID - 1])

        return false; // invalid or occupied
    bedsOccupied[bedID - 1] = true;
    return true;
}
