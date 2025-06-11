#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

/**
 * @brief Kiểm tra xem một chuỗi có phải chỉ gồm các ký tự số hay không.
 * 
 * Hàm này duyệt qua từng ký tự trong chuỗi đầu vào và kiểm tra xem tất cả các ký tự
 * đều là chữ số (0-9). Nếu có bất kỳ ký tự nào không phải là số, hàm sẽ trả về false.
 * Ngược lại, nếu tất cả đều là số, hàm trả về true.
 * 
 * @param s Chuỗi cần kiểm tra.
 * @return true nếu chuỗi chỉ gồm các ký tự số, false nếu có ký tự không phải số.
 */
inline bool isDigitString(const std::string& s) {
    for (char c : s) if (!isdigit(c)) return false;
    return true;
}

#endif //UTILS_HPP