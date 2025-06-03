#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include <vector>
#include "Patient.hpp" // Assuming Patient is a custom class



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