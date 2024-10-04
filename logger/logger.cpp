#include "logger.h"

std::shared_ptr<spdlog::logger> generalLogger;
std::shared_ptr<spdlog::logger> hitLogger;

void logger::InitLogger() {
    std::chrono::time_point<std::chrono::system_clock> date =
        global_config_manager.GetAppConfig().GetStartDate();
    std::string dateFolder = "logs/" + utils::time::GetDateInString(date);
    std::filesystem::create_directories(dateFolder);

    generalLogger = spdlog::basic_logger_mt("general_logger",
                                            dateFolder + "/general_logs.txt");
    generalLogger->set_level(spdlog::level::info);

    hitLogger =
        spdlog::basic_logger_mt("hit_logger", dateFolder + "/hit_logs.txt");
    hitLogger->set_level(spdlog::level::info);
}

std::shared_ptr<spdlog::logger> logger::GetGeneralLogger() {
    return generalLogger;
}

std::shared_ptr<spdlog::logger> logger::GetHitLogger() { return hitLogger; }