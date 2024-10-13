#include <config/logger-config.h>

const std::shared_ptr<spdlog::logger>& config::LoggerConfig::GetGeneralLogger()
    const {
    return general_logger_;
}

const std::shared_ptr<spdlog::logger>& config::LoggerConfig::GetHitLogger()
    const {
    return hit_logger_;
}

const std::string& config::LoggerConfig::GetDateFolder() const {
    return date_folder_;
}

config::LoggerConfig::LoggerConfig() {
    date_folder_ =
        "logs/" + utils::time::GetDateInString(
                      global_config_manager.GetAppConfig().GetStartDate());
    general_logger_ = spdlog::basic_logger_mt(
        "general_logger", date_folder_ + "/general_logs.txt");
    hit_logger_ =
        spdlog::basic_logger_mt("hit_logger", date_folder_ + "/hit_logs.txt");
}