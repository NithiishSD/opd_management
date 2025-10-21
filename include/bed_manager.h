#ifndef bed_manager_h
#define bed_manager_h

#include <queue>
#include <vector>
#include "hash_table.h"
using namespace std;

class BedManager
{
private:
    HashTable beds;
    priority_queue<int, vector<int>, greater<int>> freeBeds;

public:
    BedManager(int size = 20) : beds(size) {}
    int allocateBed();
    void releaseBed(int bedID);
    int getAvailableCount() const;
    bool isBedAvailable() const;
};

#endif
