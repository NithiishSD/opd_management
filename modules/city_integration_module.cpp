#include "../include/city_integration_module.h"
#include "../include/greedy.h"
#include <iostream>

using namespace std;

Hospital *CityIntegrationModule::assignPatientToNearestHospital(Patient &p)
{
    vector<Hospital *> candidates;
    // Try hospitals in same location
    for (auto h : hospitals)
    {
        if (h->getLocationName() == p.getLocationName())
            candidates.push_back(h);
    }

    // If no same-location hospital,consider all hospitals
    if (candidates.empty())
    {
        for (auto h : hospitals)
            candidates.push_back(h);
    }

    // Use greedy allocation
    GreedyAllocation allocator;
    Hospital *hospital = allocator.assignPatientToHospital(p, candidates);

    return hospital;
}
CityIntegrationModule::CityIntegrationModule(const std::vector<Hospital *> &hospList)
{
    hospitals.clear();
    for (auto hptr : hospList)
        hospitals.push_back(hptr); // copy objects
}
