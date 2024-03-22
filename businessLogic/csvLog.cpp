#include <ctime>
#include "csvLog.h"

// csvLog::~csvLog() {
//     logFile.close();
// }
csvLog::csvLog() {
    std::string name = "logs";
    std::string time = getCurrentTime();
    std::string format = ".csv";
    std::string fileName = name + time + format;
    logFile.open(fileName);
}

std::string csvLog::getCurrentTime() {
    std::time_t time;
    std::time(&time);
    //std::stringstream ss;
    //ss << time;
    std::string ts;// = ss.str();
    return ts;
}

void csvLog::logEvent(char str) {

    if (logFile.is_open()) {
        logFile << "Cartridge "
                << str
                << ", "
                << getCurrentTime()
                << std::endl;
    }
}