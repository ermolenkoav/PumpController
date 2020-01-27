#pragma once
#include "pch.h"
#include "common.h"
#include <iomanip>
#include <ctime>

class csvLog {
    template<typename T>
    utility::string_t toString(const T &t);
    utility::string_t getCurrentTime();
	utility::ofstream_t logFile;
public:
	csvLog();
	~csvLog();
	void logEvent(utility::char_t);
};