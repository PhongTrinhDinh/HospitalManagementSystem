#include "..\include\MedicalRecord.hpp"

MedicalRecord::MedicalRecord(const Time& arr, bool exam)
    : arrivalTime(arr), examined(exam) {}

// Hàm khởi tạo MedicalRecord.
// arr: Thời gian đến khám.
// exam: Thời gian khám bệnh.
// diag: Chuẩn đoán bệnh.
// pres: Đơn thuốc.
// Mặc định đã khám (examined = true).
MedicalRecord::MedicalRecord(const Time& arr, const Time& exam, const std::string& diag, const std::string& pres)
    : arrivalTime(arr), examTime(exam), diagnosis(diag), prescription(pres), examined(true) {}