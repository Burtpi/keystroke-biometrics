#ifndef UTILS_TIME_H_
#define UTILS_TIME_H_

#include <chrono>
#include <sstream>

namespace utils::time {
std::string GetDateInString(
    std::chrono::time_point<std::chrono::system_clock> time);
std::string CalculateElapsedTime();
void SleepHighResolution();
}  // namespace utils::time

#endif