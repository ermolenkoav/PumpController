#include "csvLog.h"

csvLog::~csvLog() {
    logFile.close();
}
csvLog::csvLog() {
    utility::string_t name = L"logs";
    utility::string_t time = getCurrentTime();
    utility::string_t format = L".csv";
    utility::string_t fileName(name /*+ time*/ + format);
    utility::ofstream_t logFile(fileName);
}
utility::char_t* csvLog::getCurrentTime() {
   std::time_t result = std::time(nullptr);
    return _wctime(&result);
}
void csvLog::logEvent(utility::char_t str) {
    auto wrStr = str;
    if (logFile.is_open()) 
    {
        logFile << "Cartridge " << wrStr << ', ' << getCurrentTime() << std::endl;
    }
}