# HospitalManagementSystem

Đây là nơi lưu mã nguồn của bài tập lớn cuối kỳ môn Cấu trúc dữ liệu và giải thuật - MI3060.

Đại học Bách khoa Hà Nội - HUST

Cảm ơn sự góp mặt của các thành viên nhóm 12 lớp 158237:
* Nguyễn Khắc Chí
* Hoàng Quang Huy
* Phạm Thị Quỳnh

## Build

Yêu cầu: g++, gdb, VS Code (khuyến nghị). Bên cạnh đó khuyến nghị dùng MSYS2 trên Windows.

Tạo thư mục bin nếu chưa có: mkdir bin
 
Build bằng VS Code (Ctrl + Shift + B) hoặc build thủ công: g++ src/*.cpp -g -std=c++17 -o bin/main.exe

## Lưu ý / Notice:

Khi tải folder về, để chương trình hoạt động tốt, hãy đảm bảo cập nhật defaultCSVFile trong HospitalManager.hpp thành đường dẫn đầy đủ của file dùng cho chương trình
