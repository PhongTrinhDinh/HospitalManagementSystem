#include "..\include\HospitalManager.hpp"
#include "..\include\patient.hpp"
#include "..\include\utils.hpp"
#include "..\include\readfile.hpp"
#include "..\include\writefile.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>


HospitalManager::HospitalManager() : dailyCounter(0) {
    loadPatientsFromCSV(defaultCSVFile);
}

void HospitalManager::loadPatientsFromCSV(const std::string& file_name) {
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

void HospitalManager::savePatientToCSV(const Patient& patient) {
    try {
        CSVwriter::writePatientToCSV(defaultCSVFile, patient);
    } catch (const std::exception& e) {
        std::cerr << "Lỗi khi lưu bệnh nhân vào file CSV: " << e.what() << std::endl;
    }
}

void HospitalManager::saveAllPatientsToCSV() {
    try {
        CSVwriter::writePatientsToCSV(defaultCSVFile, patients);
    } catch (const std::exception& e) {
        std::cerr << "Lỗi khi lưu danh sách bệnh nhân vào file CSV: " << e.what() << std::endl;
    }
}

void HospitalManager::rebuildQueue() {
    waitingQueue = MinHeap();
    for (auto& p : patients) {
        if (p.hasUnExaminedRecords()) { 
            waitingQueue.push(&p);
        }
    }
}

void HospitalManager::displayPatientHeader() {
    std::cout << std::left
         << std::setw(5)  << "STT " 
         << std::setw(20) << "Căn cước công dân "
         << std::setw(28) << "Họ tên "
         << std::setw(9)  << "Tuổi "
         << std::setw(15) << "Giới tính "
         << std::setw(13) << "Ưu tiên "
         << std::setw(25) << "Thời gian đăng ký "
         << std::setw(21) << "Trạng thái "
         << "\n";
}

void HospitalManager::displayPatientRow(Patient* p) {
    std::cout << std::left
         << std::setw(5)  << p->getOrder()
         << std::setw(20) << p->getID()
         << std::setw(28) << p->name.substr(0, 24)
         << std::setw(9)  << p->age
         << std::setw(15) << (p->gender ? "Nam" : "Nữ")
         << std::setw(13) << p->getPriority() 
         << std::setw(22);

    p->getArrivalTime().display();
    
    std::string status = "Đã khám hết";
    for (const auto& record : p->getMedicalHistory()) {
        if (!record.examined) {
            status = "Còn lượt chưa khám";
            break;
        }
    }
    
    std::cout << std::setw(18) << status << "\n";
}

void HospitalManager::addPatient() {
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
            
            bool exists = false;
            for (const auto& p : patients) {
                if (p.getID() == id) {
                    exists = true;
                    break;
                }
            }
            if(exists) {
                std::cout << "Căn cước công dân đã tồn tại!\n";
            } else {
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
        patientSearch.addPatient(&patients.back()); // Add to search hash table
        savePatientToCSV(patients.back()); // Lưu bệnh nhân mới vào file CSV
        std::cout << "Thêm bệnh nhân thành công!\n";
        rebuildQueue();
    } 
    catch (const char* msg) {
        std::cout << "Lỗi: " << msg << std::endl;
    }
}

void HospitalManager::deletePatient() {
    std::string id;
    std::cout << "Nhập số căn cước công dân của bệnh nhân cần xoá: ";
    std::cin >> id;

    auto it = std::remove_if(patients.begin(), patients.end(),
        [id](const Patient& p) { return p.getID() == id; });

    if (it != patients.end()) {
        patientSearch.removePatient(&(*it)); // Remove from search hash table
        patients.erase(it, patients.end());
        saveAllPatientsToCSV(); // Cập nhật file CSV sau khi xóa
        std::cout << "Đã xoá bệnh nhân!\n";
        rebuildQueue();
    } else {
        std::cout << "Không tìm thấy bệnh nhân!\n";
    }
}

void HospitalManager::updatePatient() {
    std::string id;
    std::cout << "Nhập số căn cước công dân của bệnh nhân cần cập nhật: ";
    std::cin >> id;

    for (auto& p : patients) {
        if (p.getID() == id) {
            patientSearch.removePatient(&p); // Remove old entry from search hash table
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
            patientSearch.addPatient(&p); // Re-add updated patient to search hash table
            saveAllPatientsToCSV(); // Cập nhật file CSV sau khi sửa
            std::cout << "Cập nhật thành công!\n";
            rebuildQueue();
            return;
        }
    }
    std::cout << "Không tìm thấy bệnh nhân!\n";
}

void HospitalManager::markExamined() {
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

void HospitalManager::displayMedicalHistory() {
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

void HospitalManager::displayAllPatients() {
    std::cout << "\n=== DANH SÁCH TẤT CẢ BỆNH NHÂN ===\n";
    displayPatientHeader();
    for (auto& p : patients) {
        displayPatientRow(&p);
    }
}

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

Patient* HospitalManager::searchByID(const std::string& id) {
    return patientSearch.searchByID(id);
}

Patient* HospitalManager::searchByName(const std::string& name) {
    return patientSearch.searchByName(name);
}

Patient* HospitalManager::searchByPhone(const std::string& phone) {
    return patientSearch.searchByPhone(phone);
}

Patient* HospitalManager::searchByAge(int age) {
    return patientSearch.searchByAge(age);
}