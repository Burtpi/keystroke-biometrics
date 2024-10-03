#ifndef UTILS_H_
#define UTILS_H_

#include <sstream>
#include <chrono>

namespace utils::time
{
    std::string GetDateInString(std::chrono::time_point<std::chrono::system_clock> time);
    std::string CalculateElapsedTime();
}

#endif