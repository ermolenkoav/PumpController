#pragma once
#include "pch.h"
#include <iomanip>
#include <ctime>

class csvLog final {
	std::string getCurrentTime();
    std::ofstream logFile;

public:
	explicit csvLog();
	~csvLog();
	void logEvent(char);
};