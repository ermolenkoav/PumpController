#include "csvLog.h"

csvLog::~csvLog() {
    logFile.close();
}
csvLog::csvLog() {
    std::wstring name = L"logs";
    std::wstring time = getCurrentTime();
    std::wstring format = L".json";
    std::wstring fileName(name + time + format);
    std::wofstream logFile(fileName);
}
wchar_t* csvLog::getCurrentTime() {
    std::time_t result = std::time(nullptr);
    return _wctime(&result);
}
void csvLog::logEvent(char str) {
    wchar_t wstr;
    mbtowc(&wstr, &str, 1);
    if (logFile.is_open()) {
        logFile << "Catridg " << wstr << ', ' << getCurrentTime() << std::endl;
    }
}