#include <iostream>
#include <limits>
#include <string>
#include <windows.h>
#include "../include/HospitalManager.hpp"

// Hàm đổi màu chữ trong console
void setConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Hàm hiển thị thông tin bệnh nhân
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

// Hàm xóa màn hình console
void clearScreen() {
    system("cls");
}

// Hàm hiển thị menu và trả về lựa chọn của người dùng
int displayMenu(const std::vector<std::string>& options) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    int currentSelection = 0;
    bool selected = false;

    while (!selected) {
        clearScreen();
        std::cout << "\n======= HỆ THỐNG QUẢN LÝ BỆNH VIỆN =======\n";

        // Hiển thị các tùy chọn menu
        for (size_t i = 0; i < options.size(); ++i) {
            if (i == currentSelection) {
                // Tô màu cho tùy chọn đang chọn
                setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE);
                std::cout << "> " << options[i] << " <\n";
                setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Đặt lại màu
            } else {
                std::cout << "  " << options[i] << "\n";
            }
        }

        // Hướng dẫn sử dụng
        std::cout << "\nSử dụng phím mũi tên LÊN/XUỐNG để di chuyển, ENTER để chọn.\n";

        // Xử lý đầu vào phím
        INPUT_RECORD inputRecord;
        DWORD eventsRead;
        HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
        ReadConsoleInput(hInput, &inputRecord, 1, &eventsRead);

        if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown) {
            switch (inputRecord.Event.KeyEvent.wVirtualKeyCode) {
            case VK_UP:
                currentSelection = (currentSelection - 1 + options.size()) % options.size();
                break;
            case VK_DOWN:
                currentSelection = (currentSelection + 1) % options.size();
                break;
            case VK_RETURN:
                selected = true;
                break;
            }
        }
    }

    return currentSelection;
}

int main() {
    HospitalManager manager;

    // Thiết lập mã hóa UTF-8 để hiển thị tiếng Việt
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Danh sách các tùy chọn menu
    std::vector<std::string> menuOptions = {
        "Thêm bệnh nhân mới",
        "Xóa thông tin bệnh nhân",
        "Cập nhật thông tin bệnh nhân",
        "Đánh dấu đã khám",
        "Hiển thị toàn bộ bệnh nhân",
        "Gọi 5 bệnh nhân tiếp theo",
        "Hiển thị danh sách chờ khám",
        "Tra cứu lịch sử khám",
        "Tìm kiếm bệnh nhân theo CCCD",
        "Tìm kiếm bệnh nhân theo tên",
        "Tìm kiếm bệnh nhân theo số điện thoại",
        "Tìm kiếm bệnh nhân theo tuổi",
        "Tải bệnh nhân từ file CSV",
        "Lưu tất cả bệnh nhân vào file CSV",
        "Thoát chương trình"
    };
    
    while (true) {
        // Hiển thị menu và lấy lựa chọn
        int choice = displayMenu(menuOptions);

        // Xóa màn hình trước khi xử lý
        clearScreen();

        // Xử lý lựa chọn của người dùng
        switch (choice) {
        case 0: // Thêm bệnh nhân
            manager.addPatient();
            break;

        case 1: // Xóa bệnh nhân
            manager.deletePatient();
            break;

        case 2: // Cập nhật thông tin bệnh nhân
            manager.updatePatient();
            break;

        case 3: // Đánh dấu đã khám
            manager.markExamined();
            break;

        case 4: // Hiển thị toàn bộ bệnh nhân
            manager.displayAllPatients();
            break;

        case 5: // Gọi 5 bệnh nhân tiếp theo
            manager.showNextPatients();
            break;

        case 6: // Hiển thị danh sách chờ khám
            manager.showWaitingList();
            break;

        case 7: // Tra cứu lịch sử khám
            manager.displayMedicalHistory();
            break;

        case 8: { // Tìm kiếm theo CCCD
            std::string id;
            std::cout << "Nhập số căn cước công dân: ";
            std::getline(std::cin, id);
            Patient* p = manager.searchByID(id);
            displayPatient(p);
            break;
        }

        case 9: { // Tìm kiếm theo tên
            std::string name;
            std::cout << "Nhập tên bệnh nhân: ";
            std::getline(std::cin, name);
            auto results = manager.searchByName(name);
            if (results.empty()) {
                std::cout << "Không tìm thấy bệnh nhân nào!\n";
            } else {
                std::cout << "\nTìm thấy " << results.size() << " bệnh nhân:\n";
                for (auto p : results) {
                    displayPatient(p);
                    std::cout << "------------------------\n";
                }
            }
            break;
        }

        case 10: { // Tìm kiếm theo số điện thoại
            std::string phone;
            std::cout << "Nhập số điện thoại: ";
            std::getline(std::cin, phone);
            Patient* p = manager.searchByPhone(phone);
            displayPatient(p);
            break;
        }

        case 11: { // Tìm kiếm theo tuổi
            std::string age_input;
            std::cout << "Nhập tuổi: ";
            std::getline(std::cin, age_input);
            try {
                int age = std::stoi(age_input);
                auto results = manager.searchByAge(age);
                if (results.empty()) {
                    std::cout << "Không tìm thấy bệnh nhân nào!\n";
                } else {
                    std::cout << "\nTìm thấy " << results.size() << " bệnh nhân:\n";
                    for (auto p : results) {
                        displayPatient(p);
                        std::cout << "------------------------\n";
                    }
                }
            } catch (...) {
                std::cout << "Tuổi không hợp lệ!\n";
            }
            break;
        }

        case 12: { // Tải bệnh nhân từ file CSV
            std::string filename;
            std::cout << "Nhập đường dẫn đến file CSV: ";
            std::getline(std::cin, filename);
            manager.loadPatientsFromCSV(filename);
            break;
        }

        case 13: { // Lưu tất cả bệnh nhân vào file CSV
            manager.saveAllPatientsToCSV();
            std::cout << "Đã lưu danh sách bệnh nhân vào file CSV!\n";
            break;
        }

        case 14: // Thoát chương trình
            std::cout << "Thoát chương trình!\n";
            return 0;

        default:
            std::cout << "Lựa chọn không hợp lệ!\n";
            break;
        }

        // Tạm dừng để người dùng xem kết quả
        std::cout << "\nNhấn phím bất kỳ để tiếp tục...";
        INPUT_RECORD inputRecord;
        DWORD eventsRead;
        HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
        do {
            ReadConsoleInput(hInput, &inputRecord, 1, &eventsRead);
        } while (!(inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown));

    }
    return 0;
}
