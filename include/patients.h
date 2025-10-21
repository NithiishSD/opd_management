#ifndef patients_h
#define patients_h

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

public:
    Patient();
    Patient(int id, string n, int a, string g, int p, string d);

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

    // Setters
    void setAssignedHospital(const string &hospital);
    void setAssignedBedID(int bedID);
};

#endif
