#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "patient.hpp"
#include <string>

struct HashNode {
    std::string key;
    int int_key;
    Patient* patient;
    HashNode* next;

    HashNode(const std::string& k, Patient* p) : key(k), int_key(0), patient(p), next(nullptr) {}

    HashNode(int k, Patient* p) : key(""), int_key(k), patient(p), next(nullptr) {}
};

// Hash table layer
/**
 * @class HashTable
 * @brief Lớp bảng băm dùng để lưu trữ và tra cứu thông tin bệnh nhân theo khóa là chuỗi hoặc số nguyên.
 *
 * Lớp này hỗ trợ các thao tác:
 *  - Thêm bệnh nhân mới với khóa là chuỗi hoặc số nguyên.
 *  - Xóa bệnh nhân dựa trên khóa.
 *  - Tìm kiếm bệnh nhân theo khóa.
 *
 * Các phương thức băm riêng biệt cho kiểu chuỗi và số nguyên giúp tăng hiệu quả tra cứu.
 *
 * @note
 *  - Bảng băm sử dụng mảng con trỏ tới HashNode để lưu trữ dữ liệu.
 *  - Kích thước bảng băm được đặt cố định là 101.
 */
class HashTable {
    private:
        static const int TABLE_SIZE = 101;
        HashNode** table;

        // Hash function for string
        size_t hashString(const std::string& key) const {
            size_t hash = 0;
            for(char c: key) {
                hash = (hash * 31 + c) % TABLE_SIZE;
            }
            return hash;
        }

        // Hash function for int
        size_t hashInt(int key) const {
            return (static_cast<size_t>(key) * 73856093) % TABLE_SIZE;
        }

    public:
        HashTable();
        ~HashTable();

        void insert(const std::string& key, Patient* patient);
        void insert(int key, Patient* patient);
        void remove(const std::string& key, Patient* patient);
        void remove(int key, Patient* patient);

        Patient* search(const std::string& key) const;
        Patient* search(int key) const;
};

#endif //HASHTABLE_HPP