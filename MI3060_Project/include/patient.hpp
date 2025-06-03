#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <string>
#include <vector>
#include "Time.hpp" 
#include "MedicalRecord.hpp" 
#include "utils.hpp"

class Patient {
    private:
        std::string ID;
        std::string phone;
        Time arrivalTime;
        int priority;
        int orderOfDay;
        std::vector<MedicalRecord> medicalHistory;

        bool validateID() const;
        bool validatePhone() const;

    public:
        std::string name;
        int age;
        bool gender;
        bool emergency;
        bool pregnant;

        Patient(const std::string& id, const std::string& ph, const Time& t, const std::string& n, int a, bool g, bool em, bool pr, int order);
    
        int calculatePriority();
    
        std::string getID() const;
        std::string getPhone() const;
        Time getArrivalTime() const;
        int getPriority() const;
        int getOrder() const;
    
        void markRecordExamined(int index, const Time& examTime, const std::string& diag, const std::string& pres);
        bool hasUnExaminedRecords() const;
        void updateInfo(std::string newName, std::string newPhone, int newAge, bool newGender, bool newEmergency, bool newPregnant);
        void addMedicalRecord(const Time& arr);
        const std::vector<MedicalRecord>& getMedicalHistory() const;

};

#endif //PATIENT_HPP