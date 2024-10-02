#include "utils.h"
#include <filesystem>
#include <chrono>
#include <iomanip>

std::string utils::GetCurrentDate()
{
    std::chrono::time_point<std::chrono::system_clock> time_now = std::chrono::system_clock::now();
    __time64_t time_now_in_t = std::chrono::system_clock::to_time_t(time_now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_now_in_t), "%Y-%m-%d_%H-%M-%S");
    return ss.str();
}