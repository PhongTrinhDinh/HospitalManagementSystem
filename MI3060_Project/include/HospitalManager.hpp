#ifndef HOSPITALMANAGER_HPP
#define HOSPITALMANAGER_HPP

#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
#include "Patient.hpp"
#include "minHeap.hpp"
#include "search.hpp"
#include "utils.hpp"
#include "readfile.hpp"
#include "writefile.hpp"


/**
 * @class HospitalManager
 * @brief Quản lý các chức năng chính của hệ thống bệnh viện, bao gồm quản lý bệnh nhân, hàng đợi khám bệnh, và lưu trữ dữ liệu.
 *
 * - Lưu trữ danh sách bệnh nhân và hàng đợi chờ khám.
 * - Hỗ trợ tìm kiếm, thêm, xóa, cập nhật thông tin bệnh nhân.
 * - Đọc/ghi dữ liệu bệnh nhân từ/tới file CSV.
 * - Hiển thị danh sách bệnh nhân, lịch sử khám, và các bệnh nhân sắp được khám.
 *
 * Các phương thức chính:
 * - loadPatientsFromCSV: Đọc dữ liệu bệnh nhân từ file CSV.
 * - savePatientToCSV, saveAllPatientsToCSV: Lưu thông tin bệnh nhân vào file CSV.
 * - addPatient, deletePatient, updatePatient: Thêm, xóa, cập nhật bệnh nhân.
 * - markExamined: Đánh dấu bệnh nhân đã được khám.
 * - displayMedicalHistory, displayAllPatients, showNextPatients, showWaitingList: Hiển thị thông tin liên quan đến bệnh nhân và hàng đợi.
 * - searchByID, searchByName, searchByPhone, searchByAge: Tìm kiếm bệnh nhân theo các tiêu chí khác nhau.
 */
class HospitalManager {
private:
    std::vector<Patient> patients;
    MinHeap waitingQueue;
    int dailyCounter = 0;
    PatientSearch patientSearch;
    std::string defaultCSVFile = "F:/HUST_DOCUMENTS/MI3060_Project/data/patient_data_fixed.csv"; // thay đổi đường dẫn, tùy thuộc vào vị trí đặt 
                                                                                   // folder MI3060_PROJECT


    void rebuildQueue();
    void displayPatientHeader();
    void displayPatientRow(Patient* p);

public:
    HospitalManager();
    void loadPatientsFromCSV(const std::string& filename);
    void savePatientToCSV(const Patient& patient);
    void saveAllPatientsToCSV();
    void addPatient();
    void deletePatient();
    void updatePatient();
    void markExamined();
    void displayMedicalHistory();
    void displayAllPatients();
    void showNextPatients();
    void showWaitingList();

    Patient* searchByID(const std::string& ID);
    Patient* searchByName(const std::string& name);
    Patient* searchByPhone(const std::string& phone);
    Patient* searchByAge(int age);
};

#endif