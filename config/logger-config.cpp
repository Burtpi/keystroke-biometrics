#include <config/logger-config.h>

std::chrono::time_point<std::chrono::system_clock>
config::LoggerConfig::GetStartDate() {
    return start_date_;
}

std::shared_ptr<spdlog::logger>& config::LoggerConfig::GetGeneralLogger() {
    return general_logger_;
}

std::shared_ptr<spdlog::logger>& config::LoggerConfig::GetHitLogger() {
    return hit_logger_;
}

const std::string& config::LoggerConfig::GetDateFolder() {
    return date_folder_;
}

config::LoggerConfig::LoggerConfig() {
    start_date_ = std::chrono::system_clock::now();
    date_folder_ = "logs/" + utils::time::GetDateInString(start_date_);
    general_logger_ = spdlog::basic_logger_mt(
        "general_logger", date_folder_ + "/general_logs.txt");
    hit_logger_ =
        spdlog::basic_logger_mt("hit_logger", date_folder_ + "/hit_logs.txt");
}