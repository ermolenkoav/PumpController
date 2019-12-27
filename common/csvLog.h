#pragma once
#include "pch.h"
#include "common.h"
#include <chrono>
#include <ctime>    

class csvLog {
	wchar_t* getCurrentTime();
	std::wofstream logFile;

public:
	csvLog();
	~csvLog();
	void logEvent(char);
};