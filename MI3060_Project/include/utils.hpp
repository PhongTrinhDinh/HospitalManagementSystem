#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

inline bool isDigitString(const std::string& s) {
    for (char c : s) if (!isdigit(c)) return false;
    return true;
}

#endif //UTILS_HPP