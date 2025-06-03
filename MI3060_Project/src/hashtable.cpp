#include "..\include\hashtable.hpp"

HashTable::HashTable() {
    table = new HashNode*[TABLE_SIZE](); // Khởi tạo mảng với nullptr
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashNode* current = table[i];
        while (current != nullptr) {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}

void HashTable::insert(const std::string& key, Patient* patient) {
    size_t index = hashString(key);
    HashNode* newNode = new HashNode(key, patient);
    
    // Thêm vào đầu danh sách liên kết tại index
    newNode->next = table[index];
    table[index] = newNode;
}

void HashTable::insert(int key, Patient* patient) {
    size_t index = hashInt(key);
    HashNode* newNode = new HashNode(key, patient);
    
    // Thêm vào đầu danh sách liên kết tại index
    newNode->next = table[index];
    table[index] = newNode;
}

void HashTable::remove(const std::string& key, Patient* patient) {
    size_t index = hashString(key);
    HashNode* current = table[index];
    HashNode* prev = nullptr;

    while (current != nullptr) {
        if (current->key == key && current->patient == patient) {
            if (prev == nullptr) {
                table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void HashTable::remove(int key, Patient* patient) {
    size_t index = hashInt(key);
    HashNode* current = table[index];
    HashNode* prev = nullptr;

    while (current != nullptr) {
        if (current->int_key == key && current->patient == patient) {
            if (prev == nullptr) {
                table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

Patient* HashTable::search(const std::string& key) const {
    size_t index = hashString(key);
    HashNode* current = table[index];

    while (current != nullptr) {
        if (current->key == key) {
            return current->patient;
        }
        current = current->next;
    }
    return nullptr;
}

Patient* HashTable::search(int key) const {
    size_t index = hashInt(key);
    HashNode* current = table[index];

    while (current != nullptr) {
        if (current->int_key == key) {
            return current->patient;
        }
        current = current->next;
    }
    return nullptr;
}