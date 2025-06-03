#include "..\include\MedicalRecord.hpp"

MedicalRecord::MedicalRecord(const Time& arr, bool exam)
    : arrivalTime(arr), examined(exam) {}

MedicalRecord::MedicalRecord(const Time& arr, const Time& exam, const std::string& diag, const std::string& pres)
    : arrivalTime(arr), examTime(exam), diagnosis(diag), prescription(pres), examined(true) {}