#include "csvLog.h"

csvLog::csvLog() {}
csvLog::csvLog() {}

void logEvent(std::wstring str) {
    auto time = std::chrono::system_clock::now();
    std::time_t timeAndData = std::chrono::system_clock::to_time_t(time);
    std::cout << std::ctime(&timeAndData);

    io::CSVReader<3> in("ram.csv");
    in.read_header(io::ignore_extra_column, "vendor", "size", "speed");
    std::string vendor; int size; double speed;
    while (in.read_row(vendor, size, speed)) {
        // do stuff with the data
    }
}