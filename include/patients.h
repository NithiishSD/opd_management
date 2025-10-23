#ifndef PATIENTS_H
#define PATIENTS_H

#include <string>
#include <ctime>
using namespace std;

class Patient
{
private:
    int patientID;
    string name;
    int age;
    string gender;
    int priority;
    time_t arrivalTime;
    string disease;
    string assignedHospital;
    int assignedBedID;
    string location; // City zone or area

public:
    // Constructors
    Patient();
    Patient(int id, string n, int a, string g, int p, string d);
    Patient(int id, string n, int a, string g, int p, string d, string loc);

    // Getters
    int getPatientID() const;
    string getName() const;
    int getAge() const;
    string getGender() const;
    int getPriority() const;
    time_t getArrivalTime() const;
    string getDisease() const;
    string getAssignedHospital() const;
    int getAssignedBedID() const;
    string getLocation() const;

    // Setters
    void setAssignedHospital(const string &hospital);
    void setAssignedBedID(int bedID);
    void setLocation(const string &loc);
};

#endif
