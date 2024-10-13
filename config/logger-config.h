#ifndef LOGGER_CONFIG_H
#define LOGGER_CONFIG_H

#include <config/config-manager.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <utils/time/utils-time.h>

#include <chrono>
#include <filesystem>
#include <iomanip>
#include <sstream>

namespace config {
class LoggerConfig {
   public:
    LoggerConfig();
    const std::shared_ptr<spdlog::logger>& GetGeneralLogger() const;
    const std::shared_ptr<spdlog::logger>& GetHitLogger() const;
    std::string& GetDateFolder();

   private:
    std::shared_ptr<spdlog::logger> general_logger_;
    std::shared_ptr<spdlog::logger> hit_logger_;
    std::string date_folder_;
};
}  // namespace config

#endif
