#include "csvLog.h"

csvLog::~csvLog() {
    logFile.close();
}
csvLog::csvLog() {
    utility::string_t name = _XPLATSTR("logs");
    utility::string_t time = getCurrentTime();
    utility::string_t format = _XPLATSTR(".csv");
    utility::string_t fileName(name /*+ time*/ + format);
    utility::ofstream_t logFile(fileName);
}
utility::string_t csvLog::getCurrentTime() {
    std::time_t time;
    std::time(&time);
    utility::stringstream_t ss;
    ss << time;
    utility::string_t ts = ss.str();
    return ts;
}
void csvLog::logEvent(utility::char_t str) {
    if (logFile.is_open()) {
        logFile << _XPLATSTR("Cartridge ")
                << str
                << _XPLATSTR(", ")
                << getCurrentTime()
                << std::endl;
    }
}