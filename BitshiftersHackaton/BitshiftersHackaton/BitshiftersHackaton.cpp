// BitshiftersHackaton.cpp : Defines the entry point for the application.
//
#include "FileLogger.h"
#include "BitshiftersHackaton.h"

using namespace std;

int main()
{
    FileLogger logger;
    std::vector<std::string> logit = {"ez", "az", "amaz", "ezis"};
    logger.logToTxtFile(logit);
}
