# HospitalManagementSystem
(English below)

Đây là nơi lưu mã nguồn của bài tập lớn cuối kỳ môn Cấu trúc dữ liệu và giải thuật - MI3060.

Đại học Bách khoa Hà Nội - HUST

Cảm ơn sự góp mặt của các thành viên nhóm 12 lớp 158237:
* Nguyễn Khắc Chí
* Hoàng Quang Huy
* Phạm Thị Quỳnh

A place for our final assignment for the subject Data Structures and Algorithms - MI3060

Hanoi University of Science and Technology - HUST

In collaboration with wonderful teammates:
* Nguyen Khac Chi
* Hoang Quang Huy
* Pham Thi Quynh

## Build

Yêu cầu: g++, gdb, VS Code (khuyến nghị). Bên cạnh đó khuyến nghị dùng MSYS2 trên Windows.


 Tạo thư mục bin nếu chưa có:
 
 Create bin folder if it doesn't exist:

mkdir bin

 Build with VS Code (Ctrl+Shift+B) or manually
 
 Build bằng VS Code (Ctrl + Shift + B) hoặc build thủ công:
 
g++ src/*.cpp -g -std=c++17 -o bin/main.exe


 Run
 
 Nhấn F5 trên VS Code để debug/run
 
 Press F5 on VS Code to debug/run
 
 Hoặc chạy thủ công: [main.exe]
 
 Or run it manually: [main.exe]

 ## Lưu ý / Notice:

 Khi tải folder về, để chương trình hoạt động tốt, hãy đảm bảo cập nhật defaultCSVFile trong HospitalManager.hpp thành đường dẫn đầy đủ.

 When downloading the folder, for the program to work properly, make sure to update the defaultCSVFile in HospitalManager.hpp to the full path.
