#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <vector>
#include <list>
#include <string>
#include "Patient.hpp"
#include "hashtable.hpp"

class PatientSearch {
private:
    HashTable idTable;
    HashTable nameTable;
    HashTable phoneTable;
    HashTable ageTable;

public:
    PatientSearch() = default;
    void addPatient(Patient* patient);
    void removePatient(Patient* patient);
    Patient* searchByID(const std::string& ID) const;
    Patient* searchByName(const std::string& name) const;
    Patient* searchByAge(int age) const;
    Patient* searchByPhone(const std::string& phone) const;
    
};

#endif //SEARCH_HPP