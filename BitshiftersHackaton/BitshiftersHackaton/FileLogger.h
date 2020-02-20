#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <ctime>

#define LOGBOOK "logger.txt"

class FileLogger {
public:
    FileLogger();
    ~FileLogger();
    void logToTxtFile(std::vector<std::string> logAbleData);

private:
    std::ofstream file;

};