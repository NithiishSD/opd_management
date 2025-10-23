#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class HashTable
{
private:
    int capacity;                          // Total beds in hospital
    vector<bool> bedsOccupied;             // bedOccupied[i] = true if bed i+1 is taken
    unordered_map<int, int> patientBedMap; // patientID -> bedID

public:
    HashTable(int cap = 20);

    bool isFull() const;                         // Are all beds occupied?
    bool allocateBed(int patientID, int &bedID); // Assign first available bed to patientID
    void freeBed(int patientID);                 // Free bed assigned to patientID
    bool isAvailable(int bedID) const;           // Check if bedID is free
    void displayBeds() const;                    // Show all beds and status

    // ool allocateBed(int &bedID); // allocates a free bed and returns its ID via reference

    int getTotalBeds() const;
    int getOccupiedBeds() const;
    bool allocateBed(int bedID);
};

#endif
