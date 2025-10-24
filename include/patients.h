#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <unordered_map>

class Patient
{
private:
    int patientID;
    std::string name;
    int age;
    std::string gender;
    std::string disease;
    std::string locationName;

    int priority;       // Lower number = higher urgency
    int hospitalID;     // Assigned hospital ID (-1 if not assigned)
    int bedID;          // Assigned bed ID (-1 if not assigned)
    std::string status; // "Waiting", "Admitted", "Discharged"

public:
    Patient() = default;

    Patient(int id, const std::string &name, int age, const std::string &gender,
            const std::string &disease, const std::string &location);
    void computePriority(); // Automatically compute priority
    // Getters
    int getPatientID() const;
    std::string getName() const;
    int getAge() const;
    std::string getGender() const;
    std::string getDisease() const;
    std::string getLocationName() const;
    int getPriority() const;
    int getHospitalID() const;
    int getBedID() const;
    std::string getStatus() const;

    // Setters
    void setHospitalID(int id);
    void setBedID(int id);
    void setStatus(const std::string &s);

    // Operator for hash table usage if needed
    bool operator==(const Patient &other) const
    {
        return patientID == other.patientID;
    }
};

#endif
