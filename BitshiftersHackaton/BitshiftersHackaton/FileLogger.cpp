#include "FileLogger.h"

FileLogger::FileLogger()
{
    if (!file.is_open()) {
        file.open(LOGBOOK, std::ios::out | std::ios_base::app);
    }
}

FileLogger::~FileLogger()
{
    file.close();
}

void FileLogger::logToTxtFile(const std::vector<std::string>& logAbleData)
{
    std::time_t t = std::time(nullptr);   // get time now
    std::tm* now = std::localtime(&t);

    file << (now->tm_year + 1900)
         << '-'
         << (now->tm_mon + 1)
         << '-'
         << now->tm_mday
         << ","
         << now->tm_hour
         << ':'
         << now->tm_min
         << ':'
         << now->tm_sec
         << ',';

    for (const auto& loggedValue : logAbleData) {
        file << loggedValue << ",";
    }
    file << "\n";
}