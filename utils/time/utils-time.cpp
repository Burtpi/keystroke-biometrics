#include <windows.h>

#include <config/config-manager.h>
#include <mmsystem.h>
#include <utils/time/utils-time.h>

#include <chrono>
#include <filesystem>
#include <iomanip>
#pragma comment(lib, "winmm.lib")

std::string utils::time::GetDateInString(
    std::chrono::time_point<std::chrono::system_clock> time) {
    __time64_t time_now_in_t = std::chrono::system_clock::to_time_t(time);

    std::stringstream ss;
    ss << std::put_time(std::gmtime(&time_now_in_t), "%Y%m%dT%H%M%SZ");
    return ss.str();
}

std::string utils::time::CalculateElapsedTime() {
    std::chrono::milliseconds elapsed_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() -
            global_config_manager.GetAppConfig().GetStartDate());

    std::stringstream ss;
    ss << elapsed_time.count();
    return ss.str();
}

void utils::time::SleepHighResolution() {
    timeBeginPeriod(1);
    Sleep(1);
    timeEndPeriod(1);
}