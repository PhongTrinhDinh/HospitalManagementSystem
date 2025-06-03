#include "../include/minHeap.hpp"
#include <algorithm>

bool MinHeap::compare(Patient* a, Patient* b) const {
    if (a->getPriority() != b->getPriority())
        return a->getPriority() < b->getPriority();
    if (a->getArrivalTime() != b->getArrivalTime())
        return a->getArrivalTime() < b->getArrivalTime();
    return a->getOrder() < b->getOrder();
}

void MinHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (compare(heap[index], heap[parent])) {
            std::swap(heap[index], heap[parent]);
            index = parent;
        } else break;
    }
}

void MinHeap::heapifyDown(int index) {
    int size = heap.size();
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && compare(heap[left], heap[smallest])) 
            smallest = left;
        if (right < size && compare(heap[right], heap[smallest]))
            smallest = right;

        if (smallest == index) break;
        std::swap(heap[index], heap[smallest]);
        index = smallest;
    }
}

void MinHeap::push(Patient* patient) {
    heap.push_back(patient);
    heapifyUp(heap.size() - 1);
}

Patient* MinHeap::pop() {
    if (heap.empty()) return nullptr;

    Patient* root = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
    return root;
}

std::vector<Patient*> MinHeap::peekAll() {
    std::vector<Patient*> temp = heap;
    std::vector<Patient*> result;
    MinHeap tempHeap;
    tempHeap.heap = temp;

    while (!tempHeap.empty()) {
        result.push_back(tempHeap.pop());
    }
    return result;
}

bool MinHeap::empty() const {
    return heap.empty();
}