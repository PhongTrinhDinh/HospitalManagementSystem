#ifndef TIME_HPP
#define TIME_HPP

#include <iostream>
#include <iomanip>

/**
 * @struct Time
 * @brief Cấu trúc lưu trữ thông tin về thời gian (ngày, tháng, năm, giờ, phút, giây).
 *
 * Cung cấp các phương thức để so sánh, kiểm tra hợp lệ, nhập và hiển thị thời gian.
 *
 * Các thành phần:
 * - day: Ngày (1-31)
 * - month: Tháng (1-12)
 * - year: Năm (>= 0)
 * - hour: Giờ (0-23)
 * - minute: Phút (0-59)
 * - second: Giây (0-59)
 *
 * Các phương thức:
 * - Time(...): Hàm khởi tạo với giá trị mặc định là 01/01/2025 00:00:00.
 * - operator<: So sánh thời gian nhỏ hơn.
 * - operator==: So sánh thời gian bằng nhau.
 * - operator!=: So sánh thời gian khác nhau.
 * - isValid(): Kiểm tra thời gian có hợp lệ không.
 * - input(): Nhập thời gian từ bàn phím.
 * - display(): Hiển thị thời gian ra màn hình.
 */
struct Time {
    int day, month, year;
    int hour, minute, second;

    Time(int d = 1, int m = 1, int y = 2025, int h = 0, int min = 0, int s = 0);
    
    bool operator<(const Time& other) const;
    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;
    
    bool isValid() const;
    void input();
    void display() const;
};

#endif