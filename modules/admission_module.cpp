#include "../include/admission_module.h"

AdmissionModule::AdmissionModule(int defaultBeds)
    : beds(defaultBeds), totalBeds(defaultBeds)
{
}

AdmissionModule::AdmissionModule(const string &csvPath, int defaultBeds)
    : beds(defaultBeds), totalBeds(defaultBeds)
{
    if (!csvPath.empty())
        loadHospitalsFromCSV(csvPath);
}

void AdmissionModule::loadHospitalsFromCSV(const string &path)
{
    ifstream file(path);
    if (!file.is_open())
    {
        cerr << "[Error] Could not open hospital CSV: " << path << endl;
        return;
    }

    string line;
    getline(file, line); // skip header
    while (getline(file, line))
    {
        stringstream ss(line);
        string city, name, bedsStr;
        getline(ss, city, ',');
        getline(ss, name, ',');
        getline(ss, bedsStr, ',');

        HospitalInfo h;
        h.city = city;
        h.hospitalName = name;
        h.totalBeds = stoi(bedsStr);
        h.availableBeds = h.totalBeds;
        hospitals.push_back(h);
    }

    file.close();
    cout << "[Admission] Loaded " << hospitals.size() << " hospitals from CSV.\n";
}

bool AdmissionModule::admitPatient(Patient &p)
{
    if (hospitals.empty())
    {
        cout << "[Admission] No hospital data loaded.\n";
        return false;
    }

    for (auto &h : hospitals)
    {
        if (h.availableBeds > 0)
        {
            int bedID;
            if (beds.allocateBed(bedID)) // use new HashTable method
            {
                h.availableBeds--;
                p.setAssignedHospital(h.hospitalName);
                p.setAssignedBedID(bedID);

                cout << "[Admission] " << p.getName()
                     << " admitted to " << h.hospitalName
                     << " (Bed #" << bedID
                     << ", City: " << h.city << ")\n";
                return true;
            }
        }
    }

    cout << "[Admission] No beds available in any hospital.\n";
    return false;
}

void AdmissionModule::showBedStatus() const
{
    cout << "\nCurrent Hospital Bed Status:\n";
    for (const auto &h : hospitals)
    {
        cout << "City: " << h.city
             << " | Hospital: " << h.hospitalName
             << " | Beds Occupied: " << (h.totalBeds - h.availableBeds)
             << "/" << h.totalBeds << endl;
    }
}

void AdmissionModule::showBedStatus(int patientID) const
{
    cout << "\n Bed Status for Patient ID " << patientID << ":\n";

    // Search through all beds
    if (beds.isAvailable(patientID)) // This checks if bedID is free — you may want a mapping
    {
        cout << " No record found for this patient.\n";
    }
    else
    {
        cout << "Patient ID " << patientID << " has a bed assigned (ID not tracked here individually).\n";
    }
}
