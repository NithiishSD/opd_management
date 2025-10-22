#include "../include/utils.h"
#include <iomanip>
#include <sstream>
#include <ctime>
#include <iostream>
#include <random>
#include <thread>
#include <chrono>
using namespace std;

// ------------------- Get current time as string -------------------
string Utils::getCurrentTimeString() {
    time_t now = time(nullptr);
    char buffer[26];
    ctime_s(buffer, sizeof(buffer), &now); // safe for Windows
    string timeStr(buffer);
    if (!timeStr.empty() && timeStr.back() == '\n') {
        timeStr.pop_back();
    }
    return timeStr;
}

// ------------------- Log an event -------------------
void Utils::logEvent(const string &message) {
    cout << "[" << getCurrentTimeString() << "] " << message << endl;
}

// ------------------- Generate random number -------------------
int Utils::generateRandomNumber(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

// ------------------- Simulate delay -------------------
void Utils::simulateDelay(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}
