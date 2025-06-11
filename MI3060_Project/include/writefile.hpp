#ifndef WRITEFILE_HPP
#define WRITEFILE_HPP

#include <string>
#include <vector>
#include "patient.hpp"
#include "time.hpp"

/**
 * @class CSVwriter
 * @brief Lớp hỗ trợ ghi dữ liệu bệnh nhân ra file CSV.
 *
 * Lớp này cung cấp các phương thức tĩnh để ghi thông tin của một hoặc nhiều bệnh nhân vào file CSV.
 */

/**
 * @brief Ghi thông tin của một bệnh nhân vào file CSV.
 * 
 * @param file_name Tên file CSV sẽ được ghi dữ liệu.
 * @param patient Đối tượng bệnh nhân cần ghi vào file.
 */

/**
 * @brief Ghi thông tin của nhiều bệnh nhân vào file CSV.
 * 
 * @param file_name Tên file CSV sẽ được ghi dữ liệu.
 * @param patients Danh sách các đối tượng bệnh nhân cần ghi vào file.
 */
class CSVwriter {
    public:
        static void writePatientToCSV(const std::string& file_name, const Patient& patient);
        static void writePatientsToCSV(const std::string& file_name, const std::vector<Patient>& patients);
};

#endif