// BitshiftersHackaton.cpp : Defines the entry point for the application.
//
#include "FileLogger.h"
#include "BitshiftersHackaton.h"

using namespace std;

int main()
{
	FileLogger logger;
	std::vector<std::string> log = { "lol", "aha", "kaka" };
	for (int i = 0; i < 100; i++) {
		logger.logToTxtFile(log);
	}
	return 0;
}
