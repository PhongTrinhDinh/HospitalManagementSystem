#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include <vector>
#include "Patient.hpp" 



/**
 * @class MinHeap
 * @brief Lớp MinHeap quản lý một hàng đợi ưu tiên dạng heap tối thiểu cho các đối tượng Patient.
 *
 * Lớp này sử dụng vector để lưu trữ các con trỏ đến đối tượng Patient, đảm bảo rằng phần tử có độ ưu tiên nhỏ nhất luôn ở đầu heap.
 * Các phương thức chính bao gồm:
 *  - push(Patient*): Thêm một bệnh nhân mới vào heap.
 *  - pop(): Lấy và loại bỏ bệnh nhân có độ ưu tiên nhỏ nhất khỏi heap.
 *  - peekAll(): Trả về danh sách tất cả bệnh nhân trong heap mà không thay đổi cấu trúc heap.
 *  - empty(): Kiểm tra heap có rỗng hay không.
 *
 * Các phương thức private hỗ trợ việc duy trì tính chất của heap khi thêm hoặc loại bỏ phần tử.
 */
class MinHeap {
private:
    std::vector<Patient*> heap;
    
    bool compare(Patient* a, Patient* b) const;
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    void push(Patient* patient);
    Patient* pop();
    std::vector<Patient*> peekAll();
    bool empty() const;
};

#endif //MINHEAP_HPP