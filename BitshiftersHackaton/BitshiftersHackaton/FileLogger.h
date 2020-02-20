#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <ctime>

#define LOGBOOK "../../../PythonSQL/logs.txt"

class FileLogger {
public:
    FileLogger();
    ~FileLogger();
    void logToTxtFile(const std::vector<std::string>& logAbleData);

private:
    std::ofstream file;

};