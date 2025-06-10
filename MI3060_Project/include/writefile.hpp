#ifndef WRITEFILE_HPP
#define WRITEFILE_HPP

#include <string>
#include <vector>
#include "patient.hpp"
#include "time.hpp"

class CSVwriter {
    public:
        static void writePatientToCSV(const std::string& file_name, const Patient& patient);
        static void writePatientsToCSV(const std::string& file_name, const std::vector<Patient>& patients);
};

#endif