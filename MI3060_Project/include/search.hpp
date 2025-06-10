#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <vector>
#include <list>
#include <string>
#include "Patient.hpp"
#include "hashtable.hpp"

/**
 * @class PatientSearch
 * @brief Lớp hỗ trợ tìm kiếm thông tin bệnh nhân theo nhiều tiêu chí khác nhau.
 *
 * Lớp này sử dụng các bảng băm (HashTable) để lưu trữ và tìm kiếm bệnh nhân dựa trên:
 *  - Mã số bệnh nhân (ID)
 *  - Tên bệnh nhân
 *  - Số điện thoại
 *  - Tuổi
 *
 * Các phương thức chính:
 *  - addPatient: Thêm một bệnh nhân mới vào hệ thống tìm kiếm.
 *  - removePatient: Xóa một bệnh nhân khỏi hệ thống tìm kiếm.
 *  - searchByID: Tìm kiếm bệnh nhân theo mã số.
 *  - searchByName: Tìm kiếm bệnh nhân theo tên.
 *  - searchByAge: Tìm kiếm bệnh nhân theo tuổi.
 *  - searchByPhone: Tìm kiếm bệnh nhân theo số điện thoại.
 */
class PatientSearch {
private:
    HashTable idTable;
    HashTable nameTable;
    HashTable phoneTable;
    HashTable ageTable;

public:
    PatientSearch() = default;
    void addPatient(Patient* patient);
    void removePatient(Patient* patient);
    Patient* searchByID(const std::string& ID) const;
    Patient* searchByName(const std::string& name) const;
    Patient* searchByAge(int age) const;
    Patient* searchByPhone(const std::string& phone) const;
    
};

#endif //SEARCH_HPP