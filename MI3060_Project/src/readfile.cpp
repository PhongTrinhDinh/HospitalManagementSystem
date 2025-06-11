#include "..\include\readfile.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

/**
 * Đọc danh sách bệnh nhân từ file CSV.
 * 
 * @param file_name Tên file CSV chứa dữ liệu bệnh nhân.
 * @param dailyCounter Biến đếm số lượng bệnh nhân trong ngày (sẽ được tăng lên cho mỗi bệnh nhân đọc được).
 * @return Trả về vector chứa các đối tượng Patient đã đọc từ file.
 * @throws std::runtime_error Nếu không thể mở file hoặc dữ liệu không hợp lệ.
 */
std::vector<Patient> CSVReader::readPatientFromFile(const std::string& file_name, int& dailyCounter) {
    std::vector<Patient> patients;
    std::ifstream file(file_name);

    if(!file.is_open()) {
        throw std::runtime_error("Không thể mở file: " + file_name);
    }

    std::string line;
    std::getline(file, line); //skip head line

    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, phone, arrivalTimeStr, name, ageStr, genderStr, emergencyStr, pregnantStr;
        
        // parse CSV fields
        std::getline(ss, id, ',');
        std::getline(ss, phone, ',');
        std::getline(ss, arrivalTimeStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, ageStr, ',');
        std::getline(ss, genderStr, ',');
        std::getline(ss, emergencyStr, ',');
        std::getline(ss, pregnantStr, ',');

        // validate and convert data
        try {
            // parse arrivalTime format: DD/MM/YYYY HH:MM:SS
            int day, month, year, hour, minute, second;
            char delimiter;
            std::stringstream timeStream(arrivalTimeStr);
            timeStream >> day >> delimiter >> month >> delimiter >> year
                       >> hour >> delimiter >> minute >> second;
            Time arrivalTime(day, month, year, hour, minute, second);

            if(!arrivalTime.isValid()) {
                throw std::runtime_error("Thời gian không hợp lệ trong dòng: " + line);
            }

            int age = std::stoi(ageStr);
            bool gender = (genderStr == "1");
            bool emergency = (emergencyStr == "1");
            bool pregnant= (pregnantStr == "1");
            ++dailyCounter;

            // create Patient and add to vector
            Patient patient(id, phone, arrivalTime, name, age, gender, emergency, pregnant, dailyCounter);
            patient.addMedicalRecord(arrivalTime);
            patients.push_back(patient);
        } catch (const std::exception& e) {
            std::cerr << "Lỗi xử lý khi nhập dòng: " << line << " - " << e.what() << std::endl;
            continue;
        }
    }

    file.close();
    return patients;
}