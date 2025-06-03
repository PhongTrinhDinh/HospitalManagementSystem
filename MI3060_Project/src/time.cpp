#include "..\include\time.hpp"
#include <ctime>

Time::Time(int d, int m, int y, int h, int min, int s)
    : day(d), month(m), year(y), hour(h), minute(min), second(s) {}

bool Time::operator<(const Time& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    if (day != other.day) return day < other.day;
    if (hour != other.hour) return hour < other.hour;
    if (minute != other.minute) return minute < other.minute;
    return second < other.second;
}

bool Time::operator==(const Time& other) const {
    return day == other.day && month == other.month && year == other.year &&
           hour == other.hour && minute == other.minute && second == other.second;
}

bool Time::operator!=(const Time& other) const {
    return !(*this == other);
}

bool Time::isValid() const {
    if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31) return false;
    
    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
        if (month == 2) daysInMonth[1] = 29;
    }
    
    return day <= daysInMonth[month-1] &&
           hour >= 0 && hour <= 23 &&
           minute >= 0 && minute <= 59 &&
           second >= 0 && second <= 59;
}

void Time::input() {
    time_t now = time(0);
    tm* ltm = localtime(&now); 
    
    day = ltm->tm_mday;
    month = ltm->tm_mon + 1; // tm_mon: 0-11 → +1 để thành 1-12
    year = 1900 + ltm->tm_year;
    hour = ltm->tm_hour;
    minute = ltm->tm_min;
    second = ltm->tm_sec;
}

void Time::display() const {
    std::cout << std::setfill('0') 
              << std::setw(2) << day << "/"
              << std::setw(2) << month << "/" 
              << std::setw(4) << year << " "
              << std::setw(2) << hour << ":" 
              << std::setw(2) << minute << ":" 
              << std::setw(2) << second
              << std::setfill(' '); // Reset về khoảng trắng
}