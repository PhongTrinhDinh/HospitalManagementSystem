# HospitalManagementSystem

Đây là nơi lưu mã nguồn của bài tập lớn cuối kỳ môn Cấu trúc dữ liệu và giải thuật - MI3060, học kỳ 2024.2.

Đại học Bách khoa Hà Nội - HUST

Cảm ơn sự góp mặt của các thành viên nhóm 12 lớp 158237:
* Nguyễn Khắc Chí - K68 Hệ thống thông tin quản lý 02
* Hoàng Quang Huy - K68 hệ thống thông tin quản lý 02
* Trịnh Đình Phong - K68 Hệ thống thông tin quản lý 02
* Phạm Thị Quỳnh - K68 Hệ thống thông tin quản lý 02

## Build

Yêu cầu: g++, gdb, VS Code (khuyến nghị). Bên cạnh đó khuyến nghị dùng MSYS2 trên Windows.

Mở Terminal (của thư mục gốc chứa chương trình) và nhập: .\build.bat

Sau khi build thành công: .\bin\main.exe

## Troubleshooting

Nếu gặp lỗi "command not found": Kiểm tra PATH của MinGW

Nếu lỗi build: Kiểm tra cấu trúc thư mục và tên file

Nếu lỗi Unicode: Đảm bảo file source được lưu dưới định dạng UTF-8

## Lưu ý / Notice:

Khi tải folder về, để chương trình hoạt động tốt, hãy đảm bảo cập nhật defaultCSVFile trong HospitalManager.hpp thành đường dẫn đầy đủ của file dùng cho chương trình
