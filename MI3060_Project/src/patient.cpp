#include "..\include\patient.hpp"
#include "..\include\utils.hpp"
#include <stdexcept>

Patient::Patient(const std::string& id, const std::string& ph, const Time& t, const std::string& n, int a, bool g, bool em, bool pr, int order)
    : ID(id), phone(ph), arrivalTime(t), name(n), age(a), gender(g), emergency(em), pregnant(pr), orderOfDay(order)
{
    if (!validateID()) throw std::runtime_error("ID khong hop le");
    if (!validatePhone()) throw std::runtime_error("So dien thoai khong hop le");
    if (age < 0 || age > 150) throw std::runtime_error("Tuoi phai tu 0 den 150");
    if(!validateGenderPergnancy()) throw std::runtime_error("Nam giới không thể có thai!");
    priority = calculatePriority();
}



bool Patient::validateID() const {
    return ID.length() == 12 && isDigitString(ID);
}

bool Patient::validatePhone() const {
    return phone.length() == 10 && isDigitString(phone);
}

bool Patient::validateGenderPergnancy() const {
    return !(gender && pregnant);
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

/**
 * Cập nhật thông tin bệnh nhân với các giá trị mới.
 * 
 * @param newName      Tên mới của bệnh nhân.
 * @param newPhone     Số điện thoại mới (phải đủ 10 chữ số).
 * @param newAge       Tuổi mới của bệnh nhân (0-150).
 * @param newGender    Giới tính mới (true: nam, false: nữ).
 * @param newEmergency Tình trạng khẩn cấp mới.
 * @param newPregnant  Trạng thái mang thai mới.
 * 
 * @throws std::runtime_error Nếu thông tin không hợp lệ (giới tính và mang thai không hợp lý, số điện thoại sai, tuổi ngoài phạm vi).
 */
void Patient::updateInfo(std::string newName, std::string newPhone, int newAge, 
                        bool newGender, bool newEmergency, bool newPregnant) {
    if(newGender && newPregnant) {
        throw std::runtime_error("Nam giới không thể có thai!");
    }
    name = newName;
    phone = newPhone;
    if(!isDigitString(phone) || phone.length() != 10) {
        throw std::runtime_error("Số điện thoại không hợp lệ!");
    }
    if(newAge < 0 || newAge > 150) {
        throw std::runtime_error("Tuổi phải từ 0 đến 150!");
    }
    age = newAge;
    gender = newGender;
    emergency = newEmergency;
    pregnant = newPregnant;
    priority = calculatePriority();
}

void Patient::addMedicalRecord(const Time& arr) {
    medicalHistory.emplace_back(arr);
    priority = calculatePriority();
}

const std::vector<MedicalRecord>& Patient::getMedicalHistory() const {
    return medicalHistory;
}