#ifndef bed_manager_h
#define bed_manager_h

#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

class BedManager
{
private:
    unordered_map<int, bool> bedStatus;
    priority_queue<int, vector<int>, greater<int>> freeBeds;

public:
    BedManager(int totalBeds);

    int allocateBed();
    void releaseBed(int bedID);
    int getAvailableCount() const;
    bool isBedAvailable() const;
};

#endif
