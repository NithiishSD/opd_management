#include "../include/bed_manager.h"
#include <iostream>
using namespace std;

// ------------------- Constructor -------------------
BedManager::BedManager(int size) : beds(size) {
    // Initialize all beds as free in the priority queue
    for (int i = 1; i <= size; i++) {
        freeBeds.push(i);
    }
}

// ------------------- Allocate Bed -------------------
// Returns bedID, or -1 if none available
int BedManager::allocateBed() {
    if (freeBeds.empty()) {
        cout << "No beds available!" << endl;
        return -1;
    }

    int bedID = freeBeds.top();
    freeBeds.pop();
    beds.allocateBed(bedID); // mark bed as occupied
    cout << "Allocated bed " << bedID << endl;
    return bedID;
}

// ------------------- Release Bed -------------------
void BedManager::releaseBed(int bedID) {
    if (!beds.isAvailable(bedID)) { // if bed is currently occupied
        beds.freeBed(bedID);
        freeBeds.push(bedID);
        cout << "Released bed " << bedID << endl;
    } else {
        cout << "Bed " << bedID << " is already free." << endl;
    }
}

// ------------------- Get Available Bed Count -------------------
int BedManager::getAvailableCount() const {
    return freeBeds.size();
}

// ------------------- Check Bed Availability -------------------
bool BedManager::isBedAvailable() const {
    return !freeBeds.empty();
}
