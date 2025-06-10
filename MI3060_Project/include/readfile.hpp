#ifndef READFILE_HPP
#define READFILE_HPP

#include <string>
#include <vector>
#include "patient.hpp"
#include "time.hpp"

/**
 * @class CSVReader
 * @brief Lớp hỗ trợ đọc dữ liệu bệnh nhân từ file CSV.
 *
 * Lớp này cung cấp phương thức tĩnh để đọc danh sách bệnh nhân từ file CSV
 * và cập nhật số lượng bệnh nhân mỗi ngày.
 *
 * @note Các phương thức của lớp đều là static, không cần khởi tạo đối tượng.
 */
class CSVReader {
    public:
        static std::vector<Patient> readPatientFromFile(const std::string& file_name, int& dailyCounter);
};

#endif