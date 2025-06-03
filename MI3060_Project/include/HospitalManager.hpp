#ifndef HOSPITALMANAGER_HPP
#define HOSPITALMANAGER_HPP

#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
#include "Patient.hpp"
#include "minHeap.hpp"
#include "search.hpp"
#include "utils.hpp"
#include "readfile.hpp"
#include "writefile.hpp"


class HospitalManager {
private:
    std::vector<Patient> patients;
    MinHeap waitingQueue;
    int dailyCounter = 0;
    PatientSearch patientSearch;
    std::string defaultCSVFile = "F:/HUST_DOCUMENTS/MI3060_Project/data/data.csv"; // thay đổi đường dẫn, tùy thuộc vào vị trí đặt 
                                                                                   // folder MI3060_PROJECT


    void rebuildQueue();
    void displayPatientHeader();
    void displayPatientRow(Patient* p);

public:
    HospitalManager();
    void loadPatientsFromCSV(const std::string& filename);
    void savePatientToCSV(const Patient& patient);
    void saveAllPatientsToCSV();
    void addPatient();
    void deletePatient();
    void updatePatient();
    void markExamined();
    void displayMedicalHistory();
    void displayAllPatients();
    void showNextPatients();
    void showWaitingList();

    Patient* searchByID(const std::string& ID);
    Patient* searchByName(const std::string& name);
    Patient* searchByPhone(const std::string& phone);
    Patient* searchByAge(int age);
};

#endif