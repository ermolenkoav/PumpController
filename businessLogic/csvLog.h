#pragma once
#include "pch.h"
#include <iomanip>
#include <ctime>

class csvLog {
    template<typename T>
	std::string toString(const T &t);
	std::string getCurrentTime();
	std::ofstream logFile;
public:
	csvLog();
	~csvLog();
	void logEvent(char);
};