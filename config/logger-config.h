#ifndef LOGGER_CONFIG_H
#define LOGGER_CONFIG_H

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <utils/time/utils-time.h>

#include <chrono>
#include <filesystem>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>

namespace config {
class LoggerConfig {
   public:
    LoggerConfig();
    std::chrono::time_point<std::chrono::system_clock> GetStartDate();
    std::shared_ptr<spdlog::logger>& GetGeneralLogger();
    std::shared_ptr<spdlog::logger>& GetHitLogger();
    const std::string& GetDateFolder();

   private:
    std::chrono::time_point<std::chrono::system_clock> start_date_;
    std::shared_ptr<spdlog::logger> general_logger_;
    std::shared_ptr<spdlog::logger> hit_logger_;
    std::string date_folder_;
};
}  // namespace config

#endif
