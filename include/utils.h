#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>
#include "patients.h"
#include "hospital.h"
#include "city_graph.h" // Add this include

std::vector<Patient> readPatientsFromCSV(const std::string &filename);
std::vector<Hospital> readHospitalsFromCSV(const std::string &filename);
void savePatientToCSV(const char *filename, const Patient &patient);
std::string trim(const std::string &str);
bool isNumber(const std::string &s);
Patient *findPatientByID(std::vector<Patient> &patients, int patientID);
Hospital *findHospitalByID(std::vector<Hospital> &hospitals, int hospitalID);
// New function to initialize hospital connections
void initializeHospitalConnections(CityGraph &graph, const std::vector<Hospital> &hospitals);
#endif