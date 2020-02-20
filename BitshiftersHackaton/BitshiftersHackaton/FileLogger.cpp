#include "FileLogger.h"

FileLogger::FileLogger() {
    if (!file.is_open()) {
        file.open(LOGBOOK);
    }
}

FileLogger::~FileLogger() {
    file.close();
}

void FileLogger::logToTxtFile(std::vector<std::string> logAbleData) {
    
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);

    file << (now->tm_year + 1900)
         << '-'
         << (now->tm_mon + 1)
         << '-'
         << now->tm_mday
         << ",";

    for (auto logedValue : logAbleData) {
        file << logedValue << ",";
    }
    file << "\n";
}