#include "..\include\HospitalManager.hpp"
#include "..\include\patient.hpp"
#include "..\include\utils.hpp"
#include "..\include\readfile.hpp"
#include "..\include\writefile.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <windows.h>

// Hàm khởi tạo HospitalManager, tải dữ liệu bệnh nhân từ file CSV
HospitalManager::HospitalManager() : dailyCounter(0) {
    loadPatientsFromCSV(defaultCSVFile);
}

// Đọc danh sách bệnh nhân từ file CSV
void HospitalManager::loadPatientsFromCSV(const std::string& file_name) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    try {
        patients = CSVReader::readPatientFromFile(file_name, dailyCounter);
        for(auto& p : patients) {
            patientSearch.addPatient(&p);
        }
        rebuildQueue();
        std::cout << "Đã tải " << patients.size() << " bệnh nhân từ file " << file_name << ".\n";
    } catch(const std::exception& e) {
        std::cerr << "Lỗi khi tải file!" << e.what() << std::endl;
    }
}

// Lưu một bệnh nhân mới vào file CSV
void HospitalManager::savePatientToCSV(const Patient& patient) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    try {
        CSVwriter::writePatientToCSV(defaultCSVFile, patient);
    } catch (const std::exception& e) {
        std::cerr << "Lỗi khi lưu bệnh nhân vào file CSV: " << e.what() << std::endl;
    }
}

// Lưu toàn bộ danh sách bệnh nhân vào file CSV
void HospitalManager::saveAllPatientsToCSV() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    try {
        CSVwriter::writePatientsToCSV(defaultCSVFile, patients);
    } catch (const std::exception& e) {
        std::cerr << "Lỗi khi lưu danh sách bệnh nhân vào file CSV: " << e.what() << std::endl;
    }
}

// Xây dựng lại hàng đợi bệnh nhân chờ khám
void HospitalManager::rebuildQueue() {
    waitingQueue = MinHeap();
    for (auto& p : patients) {
        if (p.hasUnExaminedRecords()) { 
            waitingQueue.push(&p);
        }
    }
}

// Hiển thị tiêu đề bảng danh sách bệnh nhân
void HospitalManager::displayPatientHeader() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::cout << std::left
         << std::setw(5)  << "STT " 
         << std::setw(20) << "Căn cước công dân "
         << std::setw(28) << "Họ tên "
         << std::setw(9)  << "Tuổi "
         << std::setw(15) << "Giới tính "
         << std::setw(13) << "Ưu tiên "
         << std::setw(30) << "Thời gian đăng ký "
         << std::setw(21) << "Trạng thái "
         << "\n";
}

// Hiển thị thông tin một bệnh nhân trên một dòng
void HospitalManager::displayPatientRow(Patient* p) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::cout << std::left
         << std::setw(5)  << p->getOrder()
         << std::setw(20) << p->getID()
         << std::setw(28) << p->name.substr(0, 24)
         << std::setw(9)  << p->age
         << std::setw(15) << (p->gender ? "Nam" : "Nữ")
         << std::setw(13) << p->getPriority() 
         << std::setw(22);

    p->getArrivalTime().display();
    
    std::string status;
    int unexaminedCount = 0;
    for (const auto& record : p->getMedicalHistory()) {
        if (!record.examined) {
            unexaminedCount++;
        }
    }
    
    if (unexaminedCount > 0) {
        status = "Còn " + std::to_string(unexaminedCount) + " lượt chưa khám";
    } else {
        status = "Đã khám hết";
    }
    
    std::cout << std::setw(18) << status << "\n";
}

// Thêm bệnh nhân mới hoặc thêm lượt khám cho bệnh nhân đã có
void HospitalManager::addPatient() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    try {
        std::string name, id, phone;
        int age;
        bool gender, emergency, pregnant;
        Time arrivalTime;

        std::cin.ignore();
        std::cout << "\nNhập tên bệnh nhân: ";
        std::getline(std::cin, name);

        while(true) {
            std::cout << "Nhập số căn cước công dân (12 chữ số): ";
            std::getline(std::cin, id);
            if(id.length() != 12 || !isDigitString(id)) {
                std::cout << "Căn cước công dân phải có 12 chữ số!\n";
                continue;
            }
            
            bool found = false;
            for(auto& p : patients) {
                if(p.getID() == id) {
                    found = true;
                    if(p.hasUnExaminedRecords()) {
                        std::cout << "Bệnh nhân này đang có lượt khám chưa được khám!\n";
                        return;
                    }
                    Time arrivalTime;
                    arrivalTime.input();
                    p.addMedicalRecord(arrivalTime);
                    rebuildQueue();
                    std::cout << "Đã thêm lượt khám mới cho bệnh nhân!\n";
                    return;
                }
            }

            if(!found) {
                break;
            }
        }

        while(true) {
            std::cout << "Nhập số điện thoại (10 chữ số): ";
            std::getline(std::cin, phone);
            if(phone.length() == 10 && isDigitString(phone)) break;
            std::cout << "Số điện thoại phải có 10 chữ số!\n";
        }

        while(true) {
            std::cout << "Nhập tuổi: ";
            std::cin >> age;
            if(age >= 0 && age <= 150) break;
            std::cout << "Tuổi phải từ 0 đến 150!\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }

        while(true) {
            std::cout << "Giới tính (1: Nam, 0: Nữ): ";
            std::cin >> gender;
            if(gender == 0 || gender == 1) break;
            std::cout << "Vui lòng nhập 0 hoặc 1!\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }

        while(true) {
            std::cout << "Cấp cứu? (1: Có, 0: Không): ";
            std::cin >> emergency;
            if(emergency == 0 || emergency == 1) break;
            std::cout << "Vui lòng nhập 0 hoặc 1!\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }

        pregnant = false;
        if (!gender) {
            while(true) {
                std::cout << "Có thai? (1: Có, 0: Không): ";
                std::cin >> pregnant;
                if(pregnant == 0 || pregnant == 1) break;
                std::cout << "Vui lòng nhập 0 hoặc 1!\n";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
        }

        arrivalTime.input();

        patients.emplace_back(id, phone, arrivalTime, name, age, gender, emergency, pregnant, ++dailyCounter);
        patients.back().addMedicalRecord(arrivalTime);
        patientSearch.addPatient(&patients.back()); // Thêm vào bảng băm tìm kiếm
        savePatientToCSV(patients.back()); // Lưu vào file CSV
        std::cout << "Thêm bệnh nhân thành công!\n";
        rebuildQueue();
    } 
    catch (const char* msg) {
        std::cout << "Lỗi: " << msg << std::endl;
    }
}

// Xoá bệnh nhân khỏi danh sách
void HospitalManager::deletePatient() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::string id;
    std::cout << "Nhập số căn cước công dân của bệnh nhân cần xoá: ";
    std::cin >> id;

    auto it = std::remove_if(patients.begin(), patients.end(),
        [id](const Patient& p) { return p.getID() == id; });

    if (it != patients.end()) {
        patientSearch.removePatient(&(*it)); // Xoá khỏi bảng băm tìm kiếm
        patients.erase(it, patients.end());
        saveAllPatientsToCSV(); // Lưu lại file CSV
        std::cout << "Đã xoá bệnh nhân!\n";
        rebuildQueue();
    } else {
        std::cout << "Không tìm thấy bệnh nhân!\n";
    }
}

// Cập nhật thông tin bệnh nhân
void HospitalManager::updatePatient() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::string id;
    std::cout << "Nhập số căn cước công dân của bệnh nhân cần cập nhật: ";
    std::cin >> id;

    for (auto& p : patients) {
        if (p.getID() == id) {
            patientSearch.removePatient(&p); // Xoá bản ghi cũ khỏi bảng băm
            std::string name, phone;
            int age;
            bool gender, emergency, pregnant;

            std::cin.ignore();
            std::cout << "Nhập tên mới (Enter để giữ nguyên): ";
            std::getline(std::cin, name);
            if (name.empty()) name = p.name;

            while(true) {
                std::cout << "Nhập số điện thoại mới (Enter để giữ nguyên): ";
                std::getline(std::cin, phone);
                if(phone.empty()) {
                    phone = p.getPhone();
                    break;
                }
                if(phone.length() == 10 && isDigitString(phone)) break;
                std::cout << "Số điện thoại phải có đúng 10 chữ số!\n";
            }

            while(true) {
                std::cout << "Nhập tuổi mới (Enter để giữ nguyên): ";
                std::string input;
                std::getline(std::cin, input);
                if(input.empty()) {
                    age = p.age;
                    break;
                }
                try {
                    age = std::stoi(input);
                    if(age >= 0 && age <= 150) break;
                    std::cout << "Tuổi phải từ 0 đến 150!\n";
                }
                catch(...) {
                    std::cout << "Tuổi không hợp lệ!\n";
                }
            }

            std::cout << "Giới tính mới (Nhập 2 để giữ nguyên): ";
            std::string genderInput;
            std::getline(std::cin, genderInput);
            gender = genderInput.empty() || genderInput == "2" ? p.gender : std::stoi(genderInput);

            std::cout << "Cấp cứu mới (Nhập 2 để giữ nguyên): ";
            std::string emergencyInput;
            std::getline(std::cin, emergencyInput);
            emergency = emergencyInput.empty() || emergencyInput == "2" ? p.emergency : std::stoi(emergencyInput);

            pregnant = p.pregnant;
            if (!gender) {
                std::cout << "Có thai mới (Nhập 2 để giữ nguyên): ";
                std::string pregnantInput;
                std::getline(std::cin, pregnantInput);
                pregnant = pregnantInput.empty() || pregnantInput == "2" ? p.pregnant : std::stoi(pregnantInput);
            }

            p.updateInfo(name, phone, age, gender, emergency, pregnant);
            patientSearch.addPatient(&p); // Thêm lại vào bảng băm
            saveAllPatientsToCSV(); // Lưu lại file CSV
            std::cout << "Cập nhật thành công!\n";
            rebuildQueue();
            return;
        }
    }
    std::cout << "Không tìm thấy bệnh nhân!\n";
}

// Đánh dấu một lượt khám đã được khám
void HospitalManager::markExamined() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::string id;
    std::cout << "Nhập số căn cước công dân: ";
    std::cin >> id;
    std::cin.ignore();
    for (auto& p : patients) {
        if (p.getID() == id) {
            std::cout << "Các lần đăng ký chưa khám:\n";
            for (size_t i = 0; i < p.getMedicalHistory().size(); ++i) {
                if (!p.getMedicalHistory()[i].examined) {
                    std::cout << i+1 << ". ";
                    p.getMedicalHistory()[i].arrivalTime.display();
                    std::cout << std::endl;
                }
            }

            int choice;
            std::cout << "Chọn lần khám cần đánh dấu (0 để hủy): ";
            std::cin >> choice;
            
            if (choice > 0 && choice <= static_cast<int>(p.getMedicalHistory().size())) {
                Time examTime;
                examTime.input();

                std::cin.ignore();
                std::string diagnosis, prescription;
                std::cout << "Nhập chuẩn đoán: ";
                std::getline(std::cin, diagnosis);
                std::cout << "Nhập đơn thuốc: ";
                std::getline(std::cin, prescription);

                p.markRecordExamined(choice-1, examTime, diagnosis, prescription);
                rebuildQueue();
                std::cout << "Đã cập nhật!\n";
            }
            return;
        }
    }
    std::cout << "Không tìm thấy bệnh nhân!\n";
}

// Hiển thị lịch sử khám bệnh của một bệnh nhân
void HospitalManager::displayMedicalHistory() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::string id;
    std::cout << "Nhập số căn cước công dân: ";
    std::cin >> id;

    for (const auto& p : patients) {
        if (p.getID() == id) {
            std::cout << "\n=== LỊCH SỬ KHÁM BỆNH ===\n";
            int stt = 1;
            for (const auto& record : p.getMedicalHistory()) {
                std::cout << "Lần " << stt++ << ": ";
                std::cout << "[" << (record.examined ? "Đã khám" : "Chưa khám") << "] ";
                record.arrivalTime.display();
                
                if (record.examined) {
                    std::cout << "\n   - Thời gian khám: ";
                    record.examTime.display();
                    std::cout << "\n   - Chuẩn đoán: " << record.diagnosis;
                    std::cout << "\n   - Đơn thuốc: " << record.prescription;
                }
                std::cout << "\n\n";
            }
            return;
        }
    }
    std::cout << "Không tìm thấy bệnh nhân!\n";
}

// Hiển thị toàn bộ danh sách bệnh nhân
void HospitalManager::displayAllPatients() {
    std::cout << "\n=== DANH SÁCH TẤT CẢ BỆNH NHÂN ===\n";
    displayPatientHeader();
    for (auto& p : patients) {
        displayPatientRow(&p);
    }
}

// Hiển thị 5 bệnh nhân tiếp theo trong hàng đợi
void HospitalManager::showNextPatients() {
    std::vector<Patient*> nextPatients = waitingQueue.peekAll();
    if (nextPatients.empty()) {
        std::cout << "\nKhông có bệnh nhân nào đang chờ khám!\n";
        return;
    }

    std::cout << "\n=== 5 BỆNH NHÂN TIẾP THEO ===\n";
    displayPatientHeader();
    for (size_t i = 0; i < std::min(nextPatients.size(), (size_t)5); ++i) {
        displayPatientRow(nextPatients[i]);
    }
}

// Hiển thị danh sách bệnh nhân đang chờ khám
void HospitalManager::showWaitingList() {
    std::vector<Patient*> waiting = waitingQueue.peekAll();
    if (waiting.empty()) {
        std::cout << "\nKhông có bệnh nhân nào đang chờ khám!\n";
        return;
    }

    std::cout << "\n=== DANH SÁCH CHỜ KHÁM ===\n";
    displayPatientHeader();
    for (auto& p : waiting) {
        displayPatientRow(p);
    }
}

// Tìm kiếm bệnh nhân theo số CCCD
Patient* HospitalManager::searchByID(const std::string& id) {
    return patientSearch.searchByID(id);
}

// Tìm kiếm bệnh nhân theo tên
Patient* HospitalManager::searchByName(const std::string& name) {
    return patientSearch.searchByName(name);
}

// Tìm kiếm bệnh nhân theo số điện thoại
Patient* HospitalManager::searchByPhone(const std::string& phone) {
    return patientSearch.searchByPhone(phone);
}

// Tìm kiếm bệnh nhân theo tuổi
Patient* HospitalManager::searchByAge(int age) {
    return patientSearch.searchByAge(age);
}