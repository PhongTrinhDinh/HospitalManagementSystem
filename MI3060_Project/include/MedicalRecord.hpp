#ifndef MEDICALRECORD_HPP
#define MEDICALRECORD_HPP

#include <string>
#include "Time.hpp" // Assuming Time is a custom class

struct MedicalRecord {
    Time arrivalTime;
    Time examTime;
    std::string diagnosis;
    std::string prescription;
    bool examined;

    MedicalRecord(const Time& arr, bool exam = false);
    MedicalRecord(const Time& arr, const Time& exam, const std::string& diag, const std::string& pres);
};

#endif