#ifndef READFILE_HPP
#define READFILE_HPP

#include <string>
#include <vector>
#include "patient.hpp"
#include "time.hpp"

class CSVReader {
    public:
        static std::vector<Patient> readPatientFromFile(const std::string& file_name, int& dailyCounter);
};

#endif