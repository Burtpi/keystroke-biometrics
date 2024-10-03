#include "utils-time.h"
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <config/config-manager.h>

std::string utils::time::GetDateInString(std::chrono::time_point<std::chrono::system_clock> time)
{
    __time64_t time_now_in_t = std::chrono::system_clock::to_time_t(time);

    std::stringstream ss;
    ss << std::put_time(std::gmtime(&time_now_in_t), "%Y%m%dT%H%M%SZ");
    return ss.str();
}

std::string utils::time::CalculateElapsedTime()
{
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() -
                                                                             global_config_manager.GetAppConfig().GetStartDate());

    std::stringstream ss;
    ss << elapsedTime.count();
    return ss.str();
}