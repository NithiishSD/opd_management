#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <ctime>
#include <thread>
#include <chrono>
#include <iostream>
#include <random>
using namespace std;

namespace Utils
{
    string getCurrentTimeString();
    void logEvent(const string &message);
    int generateRandomNumber(int min, int max);
    void simulateDelay(int milliseconds);
}

#endif
