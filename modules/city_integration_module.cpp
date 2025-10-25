#include "../include/city_integration_module.h"
#include "../include/greedy.h"
#include "../include/dijkstra.h"
#include "../include/utils.h"
#include <climits>
#include <iostream>
#include <unordered_map>

using namespace std;

CityIntegrationModule::CityIntegrationModule(const std::vector<Hospital *> &hospList) {
    hospitals.clear();
    for (auto hptr : hospList)
        hospitals.push_back(hptr);
}

void CityIntegrationModule::initializeGraph(const std::vector<Hospital> &hospitals) {
    initializeHospitalConnections(graph, hospitals);
}

Hospital *CityIntegrationModule::assignPatientToNearestHospital(Patient &p) {
    //cout << "[Debug] Assigning patient " << p.getName() << " (Location: " << p.getLocationName() << ")\n";

    // Step 1: Try hospitals in the same location
    vector<Hospital *> candidates;
    for (auto h : hospitals) {
        if (h->getLocationName() == (p.getLocationName())) {
            candidates.push_back(h);
            //cout << "[Debug] Found same-location hospital: " << h->getHospitalName() << " (ID: " << h->getHospitalID() 
              //   << ", Beds: " << h->getOccupiedBeds().size() << "/" << h->getTotalBeds() << ")\n";
        }
    }

    // Use GreedyAllocation for same-location hospitals
    GreedyAllocation allocator;
    Hospital *hospital = allocator.assignPatientToHospital(p, candidates);
    if (hospital) {
       // cout << "[Debug] Assigned to same-location hospital: " << hospital->getHospitalName() << "\n";
        return hospital;
    }
    //cout << "[Debug] No available beds in same-location hospitals\n";

    // Step 2: Use Dijkstra to find nearest hospital
    //cout << "[Debug] Running Dijkstra's algorithm\n";
    vector<int> hospitalIds;
    for (auto h : hospitals) {
        hospitalIds.push_back(h->getHospitalID());
    }
    Dijkstra dijkstra(hospitalIds);

    for (auto h : hospitals) {
        int hospitalID = h->getHospitalID();
        auto connections = graph.getConnections(hospitalID);
        // cout << "[Debug] Hospital " << h->getHospitalName() << " (ID: " << hospitalID << ") has " 
        //      << connections.size() << " connections\n";
        for (auto edge : connections) {
            dijkstra.addEdge(hospitalID, edge.to, edge.distance);
            //cout << "[Debug] Added edge to Dijkstra: " << hospitalID << " -> " << edge.to << ", Distance=" << edge.distance << "\n";
        }
    }

    // Find a hospital in the patient's location to use as the starting node
    int startHospitalID = -1;
    for (auto h : hospitals) {
        if (h->getLocationName() == p.getLocationName()) {
            startHospitalID = h->getHospitalID();
            break;
        }
    }
    if (startHospitalID == -1) {
        startHospitalID = hospitals[0]->getHospitalID();
       // cout << "[Debug] No hospital in patient's location, using hospital ID " << startHospitalID << "\n";
    } else {
        //cout << "[Debug] Starting Dijkstra from hospital ID " << startHospitalID << "\n";
    }

    // Run Dijkstra's algorithm
    vector<pair<int, int>> distances = dijkstra.shortestPath(startHospitalID);
  //  cout << "[Debug] Dijkstra returned " << distances.size() << " distances\n";

    // Find the nearest hospital with available beds
    int minDistance = INT_MAX;
    Hospital *nearestHospital = nullptr;
    for (const auto &pair : distances) { // C++11-compatible loop
        int hID = pair.first;
        int dist = pair.second;
        for (auto h : hospitals) {
            if (h->getHospitalID() == hID && dist < minDistance &&
                static_cast<int>(h->getOccupiedBeds().size()) < h->getTotalBeds()) {
                minDistance = dist;
                nearestHospital = h;
             //   cout << "[Debug] Found hospital with beds: " << h->getHospitalName() << " (ID: " << hID 
               //      << ", Distance: " << dist << ", Beds: " << h->getOccupiedBeds().size() << "/" << h->getTotalBeds() << ")\n";
            }
        }
    }

    // Assign patient to the nearest hospital with available beds
    if (nearestHospital) {
        vector<Hospital *> nearestHospitalList = {nearestHospital};
        hospital = allocator.assignPatientToHospital(p, nearestHospitalList);
        if (hospital) {
            cout << "[CityIntegration] Assigned patient " << p.getName() << " to nearest hospital "
                 << hospital->getHospitalName() << " (Distance: " << minDistance << ")\n";
            return hospital;
        }
    }

    // No hospital with available beds found
    p.setStatus("Waiting");
    cout << "[CityIntegration] No beds available in any hospital for patient " << p.getName() << "\n";
    return nullptr;
}

string CityIntegrationModule::getHospitalName(int hospitalID) const {
    for (auto h : hospitals) {
        if (h->getHospitalID() == hospitalID)
            return h->getHospitalName();
    }
    return "";
}