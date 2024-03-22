#pragma once
#include <fstream>
#include <string>

class csvLog final {
	static std::string getCurrentTime();
    std::ofstream logFile;

public:
	explicit csvLog();
	~csvLog();
	void logEvent(char);
};
