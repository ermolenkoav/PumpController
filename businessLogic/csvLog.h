#pragma once
#include "pch.h"
#include "common.h"
#include <chrono>
#include <ctime>    

class csvLog {
	utility::char_t* getCurrentTime();
	utility::ofstream_t logFile;

public:
	csvLog();
	~csvLog();
	void logEvent(utility::char_t);
};