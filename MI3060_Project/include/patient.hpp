#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <string>
#include <vector>
#include "Time.hpp" 
#include "MedicalRecord.hpp" 
#include "utils.hpp"

/**
 * @class Patient
 * @brief Đại diện cho một bệnh nhân trong hệ thống quản lý bệnh viện.
 *
 * Lưu trữ thông tin cá nhân, lịch sử khám bệnh và các thuộc tính liên quan đến ưu tiên khám.
 *
 * Thuộc tính:
 * - ID: Mã định danh bệnh nhân.
 * - phone: Số điện thoại liên hệ.
 * - arrivalTime: Thời gian bệnh nhân đến.
 * - priority: Mức độ ưu tiên khám bệnh.
 * - orderOfDay: Thứ tự đến trong ngày.
 * - medicalHistory: Danh sách lịch sử khám bệnh.
 * - name: Họ tên bệnh nhân.
 * - age: Tuổi bệnh nhân.
 * - gender: Giới tính (true: nam, false: nữ).
 * - emergency: Có phải trường hợp cấp cứu không.
 * - pregnant: Có đang mang thai không (áp dụng cho nữ).
 *
 * Phương thức:
 * - Patient(...): Hàm khởi tạo bệnh nhân với đầy đủ thông tin.
 * - calculatePriority(): Tính toán mức độ ưu tiên khám bệnh.
 * - getID(), getPhone(), getArrivalTime(), getPriority(), getOrder(): Lấy thông tin tương ứng.
 * - markRecordExamined(...): Đánh dấu một lần khám bệnh đã được thực hiện.
 * - hasUnExaminedRecords(): Kiểm tra còn lần khám nào chưa được thực hiện không.
 * - updateInfo(...): Cập nhật thông tin cá nhân của bệnh nhân.
 * - addMedicalRecord(...): Thêm một lần khám mới vào lịch sử.
 * - getMedicalHistory(): Lấy danh sách lịch sử khám bệnh.
 *
 * Các hàm kiểm tra hợp lệ (private):
 * - validateID(): Kiểm tra mã bệnh nhân hợp lệ.
 * - validatePhone(): Kiểm tra số điện thoại hợp lệ.
 * - validateGenderPergnancy(): Kiểm tra tính hợp lệ giữa giới tính và tình trạng mang thai.
 */
class Patient {
    private:
        std::string ID;
        std::string phone;
        Time arrivalTime;
        int priority;
        int orderOfDay;
        std::vector<MedicalRecord> medicalHistory;

        bool validateID() const;
        bool validatePhone() const;
        bool validateGenderPergnancy() const;

    public:
        std::string name;
        int age;
        bool gender;
        bool emergency;
        bool pregnant;

        Patient(const std::string& id, const std::string& ph, const Time& t, const std::string& n, int a, bool g, bool em, bool pr, int order);
    
        int calculatePriority();
    
        std::string getID() const;
        std::string getPhone() const;
        Time getArrivalTime() const;
        int getPriority() const;
        int getOrder() const;
    
        void markRecordExamined(int index, const Time& examTime, const std::string& diag, const std::string& pres);
        bool hasUnExaminedRecords() const;
        void updateInfo(std::string newName, std::string newPhone, int newAge, bool newGender, bool newEmergency, bool newPregnant);
        void addMedicalRecord(const Time& arr);
        const std::vector<MedicalRecord>& getMedicalHistory() const;

};

#endif //PATIENT_HPP