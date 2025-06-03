#include "..\include\patient.hpp"
#include "..\include\utils.hpp"
#include <stdexcept>

Patient::Patient(const std::string& id, const std::string& ph, const Time& t, const std::string& n, int a, bool g, bool em, bool pr, int order)
    : ID(id), phone(ph), arrivalTime(t), name(n), age(a), gender(g), emergency(em), pregnant(pr), orderOfDay(order)
{
    if (!validateID()) throw std::runtime_error("ID khong hop le");
    if (!validatePhone()) throw std::runtime_error("So dien thoai khong hop le");
    if (age < 0 || age > 150) throw std::runtime_error("Tuoi phai tu 0 den 150");
    priority = calculatePriority();
}



bool Patient::validateID() const {
    return ID.length() == 12 && isDigitString(ID);
}

bool Patient::validatePhone() const {
    return phone.length() == 10 && isDigitString(phone);
}


int Patient::calculatePriority() {
    if (emergency) return 0;
    if (!gender && pregnant) return 1;
    if (age < 6 || age > 75) return 1;
    return 2;
}

std::string Patient::getID() const { return ID; }
std::string Patient::getPhone() const { return phone; }
Time Patient::getArrivalTime() const { return arrivalTime; }
int Patient::getPriority() const { return priority; }
int Patient::getOrder() const { return orderOfDay; }

void Patient::markRecordExamined(int index, const Time& examTime, 
                               const std::string& diag, const std::string& pres) {
    if (index >= 0 && index < static_cast<int>(medicalHistory.size())) {
        medicalHistory[index].examined = true;
        medicalHistory[index].examTime = examTime;
        medicalHistory[index].diagnosis = diag;
        medicalHistory[index].prescription = pres;
    }
}

bool Patient::hasUnExaminedRecords() const {
    for (const auto& record : medicalHistory) {
        if (!record.examined) return true;
    }
    return false;
}

void Patient::updateInfo(std::string newName, std::string newPhone, int newAge, 
                        bool newGender, bool newEmergency, bool newPregnant) {
    name = newName;
    phone = newPhone;
    age = newAge;
    gender = newGender;
    emergency = newEmergency;
    pregnant = newPregnant;
    priority = calculatePriority();
}

void Patient::addMedicalRecord(const Time& arr) {
    medicalHistory.emplace_back(arr);
}

const std::vector<MedicalRecord>& Patient::getMedicalHistory() const {
    return medicalHistory;
}