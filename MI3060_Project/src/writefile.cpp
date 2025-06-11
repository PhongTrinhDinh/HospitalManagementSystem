#include "..\include\writefile.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

void CSVwriter::writePatientToCSV(const std::string& file_name, const Patient& patient) {
    std::ofstream file(file_name, std::ios::app); // open file in append mod
    if(!file.is_open()) {
        throw std::runtime_error("Không thể mở file để ghi: " + file_name);
    }

    // format arrivalTime
    std::stringstream timeStream;
    timeStream << std::setfill('0')
               << std::setw(2) << patient.getArrivalTime().day << "/"
               << std::setw(2) << patient.getArrivalTime().month << "/"
               << std::setw(4) << patient.getArrivalTime().year << " "
               << std::setw(2) << patient.getArrivalTime().hour << ":"
               << std::setw(2) << patient.getArrivalTime().minute << ":"
               << std::setw(2) << patient.getArrivalTime().second;

    // write patient information to file
    file << patient.getID() << ","
         << patient.getPhone() << ","
         << timeStream.str() << ","
         << patient.name << ","
         << (patient.gender ? "1" : "0") << ","
         << (patient.emergency ? "1" : "0") << ","
         << (patient.pregnant ? "1" : "0") << "\n";

    file.close();
}

/**
 * @brief Ghi danh sách bệnh nhân vào file CSV.
 * 
 * @param filename Tên file CSV để ghi dữ liệu.
 * @param patients Danh sách các bệnh nhân cần ghi.
 * @throws std::runtime_error Nếu không thể mở file để ghi.
 */
void CSVwriter::writePatientsToCSV(const std::string& filename, const std::vector<Patient>& patients) {
    std::ofstream file(filename, std::ios::out); // Mở file ở chế độ ghi mới
    if (!file.is_open()) {
        throw std::runtime_error("Không thể mở file để ghi: " + filename);
    }

    // Ghi header
    file << "ID,Phone,ArrivalTime,Name,Age,Gender,Emergency,Pregnant\n";

    // Ghi từng bệnh nhân
    for (const auto& patient : patients) {
        std::stringstream timeStream;
        timeStream << std::setfill('0') 
                   << std::setw(2) << patient.getArrivalTime().day << "/"
                   << std::setw(2) << patient.getArrivalTime().month << "/" 
                   << std::setw(4) << patient.getArrivalTime().year << " "
                   << std::setw(2) << patient.getArrivalTime().hour << ":" 
                   << std::setw(2) << patient.getArrivalTime().minute << ":" 
                   << std::setw(2) << patient.getArrivalTime().second;

        file << patient.getID() << ","
             << patient.getPhone() << ","
             << timeStream.str() << ","
             << patient.name << ","
             << patient.age << ","
             << (patient.gender ? "1" : "0") << ","
             << (patient.emergency ? "1" : "0") << ","
             << (patient.pregnant ? "1" : "0") << "\n";
    }

    file.close();
}