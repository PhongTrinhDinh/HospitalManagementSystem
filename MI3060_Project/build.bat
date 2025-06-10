@echo off
if not exist "bin" mkdir bin

g++ -o bin/main.exe ^
src/main.cpp ^
src/time.cpp ^
src/patient.cpp ^
src/MedicalRecord.cpp ^
src/minHeap.cpp ^
src/hashtable.cpp ^
src/search.cpp ^
src/HospitalManager.cpp ^
src/readfile.cpp ^
src/writefile.cpp ^
-I include ^
-std=c++17