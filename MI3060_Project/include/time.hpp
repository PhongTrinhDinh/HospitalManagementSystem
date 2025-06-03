#ifndef TIME_HPP
#define TIME_HPP

#include <iostream>
#include <iomanip>

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