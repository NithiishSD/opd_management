#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "patients.h"
#include "hospital.h"

// ================= CSV Reading =================
std::vector<Patient> readPatientsFromCSV(const std::string &filename);
std::vector<Hospital> readHospitalsFromCSV(const std::string &filename);
void savePatientToCSV(const char *filename, const Patient &patient);
// ================= String Utilities =================
std::string trim(const std::string &str);
bool isNumber(const std::string &s);

// ================= Search Utilities =================
Patient *findPatientByID(std::vector<Patient> &patients, int patientID);
Hospital *findHospitalByID(std::vector<Hospital> &hospitals, int hospitalID);

#endif
