#ifndef LOGGER_H_
#define LOGGER_H_

#include <config/config-manager.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <utils/time/utils-time.h>

#include <chrono>
#include <filesystem>
#include <iomanip>
#include <sstream>

namespace logger {
void InitLogger();

std::shared_ptr<spdlog::logger> GetGeneralLogger();
std::shared_ptr<spdlog::logger> GetHitLogger();
}  // namespace logger

#endif