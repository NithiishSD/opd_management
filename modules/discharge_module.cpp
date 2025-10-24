#include "../include/discharge_module.h"

DischargeModule::DischargeModule(std::vector<Hospital> &hospList) : hospitals(hospList) {}

void DischargeModule::dischargePatient(Patient &p)
{
    int hospitalID = p.getHospitalID();
    int bedID = p.getBedID();

    if (hospitalID < 0 || bedID < 0)
    {
        std::cout << "[Discharge] Patient " << p.getName()
                  << " is not admitted to any hospital.\n";
        return;
    }

    for (auto &h : hospitals)
    {
        if (h.getHospitalID() == hospitalID)
        {
            bool released = h.freeBed(bedID);
            if (released)
            {
                std::cout << "[Discharge] Patient " << p.getName()
                          << " discharged from hospital " << h.getHospitalName()
                          << " | Bed ID: " << bedID << "\n";

                // Reset patient bed info
                p.setBedID(-1);
                p.setHospitalID(-1);
            }
            else
            {
                std::cout << "[Discharge] Failed to free bed " << bedID
                          << " in hospital " << h.getHospitalName() << "\n";
            }
            return;
        }
    }

    std::cout << "[Discharge] Hospital with ID " << hospitalID
              << " not found for patient " << p.getName() << "\n";
}
