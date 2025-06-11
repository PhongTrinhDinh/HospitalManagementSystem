#ifndef MEDICALRECORD_HPP
#define MEDICALRECORD_HPP

#include <string>
#include "Time.hpp" 

/**
 * @struct MedicalRecord
 * @brief Lưu trữ thông tin hồ sơ bệnh án của bệnh nhân.
 *
 * Cấu trúc này chứa các thông tin liên quan đến quá trình khám chữa bệnh của một bệnh nhân,
 * bao gồm thời gian đến khám, thời gian khám, chẩn đoán, đơn thuốc và trạng thái đã được khám hay chưa.
 *
 * @var arrivalTime Thời gian bệnh nhân đến khám.
 * @var examTime Thời gian bệnh nhân được khám.
 * @var diagnosis Chuẩn đoán bệnh của bác sĩ.
 * @var prescription Đơn thuốc được kê cho bệnh nhân.
 * @var examined Trạng thái cho biết bệnh nhân đã được khám hay chưa.
 *
 * @brief Hàm khởi tạo MedicalRecord với thời gian đến khám và trạng thái đã khám (mặc định là chưa khám).
 * @param arr Thời gian bệnh nhân đến khám.
 * @param exam Trạng thái đã khám (mặc định là false).
 *
 * @brief Hàm khởi tạo MedicalRecord với đầy đủ thông tin: thời gian đến, thời gian khám, chẩn đoán và đơn thuốc.
 * @param arr Thời gian bệnh nhân đến khám.
 * @param exam Thời gian bệnh nhân được khám.
 * @param diag Chuẩn đoán bệnh.
 * @param pres Đơn thuốc.
 */
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