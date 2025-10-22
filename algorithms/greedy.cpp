#include "greedy.h"
#include <iostream>
using namespace std;

int GreedyAllocation::chooseHospital(const vector<pair<int, int>> &hospitalData)
{
    if (hospitalData.empty())
    {
        cout << " No hospital data available.\n";
        return -1;
    }

    int bestHospitalIndex = 0;
    double bestScore = 0.0;

    for (int i = 0; i < hospitalData.size(); i++)
    {
        int beds = hospitalData[i].first;
        int distance = hospitalData[i].second;

        // Avoid division by zero if hospital is at same location
        double score = (distance == 0) ? beds : static_cast<double>(beds) / distance;

        if (score > bestScore)
        {
            bestScore = score;
            bestHospitalIndex = i;
        }
    }

    cout << "Selected Hospital Index: " << bestHospitalIndex
         << " | Score: " << bestScore << endl;

    return bestHospitalIndex;
}
