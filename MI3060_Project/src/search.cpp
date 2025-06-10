#include "..\include\search.hpp"
#include <stdexcept>

void PatientSearch::addPatient(Patient* patient) {
    idTable.insert(patient->getID(), patient);
    nameTable.insert(patient->name, patient);
    phoneTable.insert(patient->getPhone(), patient);
    ageTable.insert(patient->age, patient);
}

// Xóa thông tin bệnh nhân khỏi các bảng tìm kiếm theo ID, tên, số điện thoại và tuổi.
void PatientSearch::removePatient(Patient* patient) {
    idTable.remove(patient->getID(), patient);
    nameTable.remove(patient->name, patient);
    phoneTable.remove(patient->getPhone(), patient);
    ageTable.remove(patient->age, patient);
}

Patient* PatientSearch::searchByID(const std::string& id) const {
    return idTable.search(id);
}

Patient* PatientSearch::searchByName(const std::string& name) const {
    return nameTable.search(name);
}

Patient* PatientSearch::searchByPhone(const std::string& phone) const {
    return phoneTable.search(phone);
}

Patient* PatientSearch::searchByAge(int age) const {
    if(age < 0 || age > 150) {
        throw std::invalid_argument("Tuổi phải nằm trong khoảng 0 đến 150!");
    }
    return ageTable.search(age);
}