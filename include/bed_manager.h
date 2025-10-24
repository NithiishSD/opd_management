#ifndef BED_MANAGER_H
#define BED_MANAGER_H
#include "../include/hash_table.h"
#include <queue>
#include <vector>
#include <queue>
#include <iostream>

class BedManager
{
private:
    int totalBeds;
    std::priority_queue<int, std::vector<int>, std::greater<int>> freeBeds; // Min-heap of free bed IDs
    std::vector<bool> bedOccupied;                                          // true = occupied, false = free

public:
    BedManager(int size);

    // Allocate the lowest-numbered free bed; returns -1 if full
    int allocateBed();

    // Release a bed by ID
    void releaseBed(int bedID);

    // Returns number of free beds
    int getAvailableCount() const;

    // Check if any bed is available
    bool isBedAvailable() const;

    // Optional: get occupied beds list
    std::vector<int> getOccupiedBeds() const;
};

#endif
