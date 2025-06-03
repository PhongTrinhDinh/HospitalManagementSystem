#include <iostream>
#include <limits>
#include <string>
#include <windows.h>
#include "../include/HospitalManager.hpp"

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void displayPatient(const Patient* p) {
    if (!p) {
        std::cout << "Không tìm thấy bệnh nhân!\n";
        return;
    }
    std::cout << "\n=== THÔNG TIN BỆNH NHÂN ===\n";
    std::cout << "CCCD: " << p->getID() << "\n";
    std::cout << "Họ tên: " << p->name << "\n";
    std::cout << "Tuổi: " << p->age << "\n";
    std::cout << "Giới tính: " << (p->gender ? "Nam" : "Nữ") << "\n";
    std::cout << "Cấp cứu: " << (p->emergency ? "Có" : "Không") << "\n";
    std::cout << "Có thai: " << (p->pregnant ? "Có" : "Không") << "\n";
    std::cout << "Thời gian đăng ký: ";
    p->getArrivalTime().display();
    std::cout << "\n";
    std::cout << "Ưu tiên: " << p->getPriority() << "\n";
    std::cout << "Thứ tự trong ngày: " << p->getOrder() << "\n";
}

void displayMenu() {
    std::cout << "\n======= HỆ THỐNG QUẢN LÝ BỆNH VIỆN =======\n";
    std::cout << "1. Thêm bệnh nhân mới\n";
    std::cout << "2. Xóa thông tin bệnh nhân\n";
    std::cout << "3. Cập nhật thông tin bệnh nhân\n";
    std::cout << "4. Đánh dấu đã khám\n";
    std::cout << "5. Hiển thị toàn bộ bệnh nhân\n";
    std::cout << "6. Gọi 5 bệnh nhân tiếp theo\n";
    std::cout << "7. Hiển thị danh sách chờ khám\n";
    std::cout << "8. Tra cứu lịch sử khám\n";
    std::cout << "9. Tìm kiếm bệnh nhân theo CCCD\n";
    std::cout << "10. Tìm kiếm bệnh nhân theo tên\n";
    std::cout << "11. Tìm kiếm bệnh nhân theo số điện thoại\n";
    std::cout << "12. Tìm kiếm bệnh nhân theo tuổi\n";
    std::cout << "13. Tải bệnh nhân từ file\n";
    std::cout << "14. Lưu tất cả bệnh nhân vào file CSV\n";
    std::cout << "0. Thoát chương trình\n";
    std::cout << "Lựa chọn chức năng: ";
}

int main() {
    HospitalManager manager;
    int choice;

    // Thiết lập mã hóa UTF-8 để hiển thị tiếng Việt
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    while (true) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
        case 1: // Thêm bệnh nhân
            manager.addPatient();
            break;

        case 2: // Xóa bệnh nhân
            manager.deletePatient();
            break;

        case 3: // Cập nhật thông tin bệnh nhân
            manager.updatePatient();
            break;

        case 4: // Đánh dấu đã khám
            manager.markExamined();
            break;

        case 5: // Hiển thị toàn bộ bệnh nhân
            manager.displayAllPatients();
            break;

        case 6: // Gọi 5 bệnh nhân tiếp theo
            manager.showNextPatients();
            break;

        case 7: // Hiển thị danh sách chờ khám
            manager.showWaitingList();
            break;

        case 8: // Tra cứu lịch sử khám
            manager.displayMedicalHistory();
            break;

        case 9: { // Tìm kiếm theo CCCD
            std::string id;
            std::cout << "Nhập số căn cước công dân: ";
            std::getline(std::cin, id);
            Patient* p = manager.searchByID(id);
            displayPatient(p);
            break;
        }

        case 10: { // Tìm kiếm theo tên
            std::string name;
            std::cout << "Nhập tên bệnh nhân: ";
            std::getline(std::cin, name);
            Patient* p = manager.searchByName(name);
            displayPatient(p);
            break;
        }

        case 11: { // Tìm kiếm theo số điện thoại
            std::string phone;
            std::cout << "Nhập số điện thoại: ";
            std::getline(std::cin, phone);
            Patient* p = manager.searchByPhone(phone);
            displayPatient(p);
            break;
        }

        case 12: { // Tìm kiếm theo tuổi
            std::string age_input;
            std::cout << "Nhập tuổi: ";
            std::getline(std::cin, age_input);
            try {
                int age = std::stoi(age_input);
                Patient* p = manager.searchByAge(age);
                displayPatient(p);
            } catch (...) {
                std::cout << "Tuổi không hợp lệ!\n";
            }
            break;
        }

        case 13: {
            std::cin.ignore(1000, '\n');
            std::string file_name;
            std::cout << "Nhập tên file: ";
            std::getline(std::cin, file_name);
            manager.loadPatientsFromCSV(file_name);
            break;
        }

        case 14: { // Lưu tất cả bệnh nhân vào file CSV
            manager.saveAllPatientsToCSV();
            std::cout << "Đã lưu danh sách bệnh nhân vào file CSV!\n";
            break;
        }

        case 0: // Thoát chương trình
            std::cout << "Thoát chương trình!\n";
            return 0;

        default:
            std::cout << "Chức năng không hợp lệ!\n";
            break;
        }
    }

    return 0;
}