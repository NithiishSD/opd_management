#include "../include/bed_manager.h"

BedManager::BedManager(int size) : totalBeds(size), bedOccupied(size, false)
{
    for (int i = 0; i < size; ++i)
    {
        freeBeds.push(i + 1); // bed IDs start from 1
    }
}

int BedManager::allocateBed()
{
    if (freeBeds.empty())
        return -1; // no beds available

    int bedID = freeBeds.top();
    freeBeds.pop();
    bedOccupied[bedID - 1] = true;
    return bedID;
}

void BedManager::releaseBed(int bedID)
{
    if (bedID <= 0 || bedID > totalBeds)
        return;
    if (!bedOccupied[bedID - 1])
        return;

    bedOccupied[bedID - 1] = false;
    freeBeds.push(bedID);
}

int BedManager::getAvailableCount() const
{
    return freeBeds.size();
}

bool BedManager::isBedAvailable() const
{
    return !freeBeds.empty();
}

std::vector<int> BedManager::getOccupiedBeds() const
{
    std::vector<int> occupied;
    for (int i = 0; i < totalBeds; ++i)
    {
        if (bedOccupied[i])
            occupied.push_back(i + 1);
    }
    return occupied;
}
