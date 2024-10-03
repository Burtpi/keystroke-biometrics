#ifndef LOGGER_H_
#define LOGGER_H_

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "../Config/config-manager.h"

namespace logger
{
    void InitLogger();

    std::shared_ptr<spdlog::logger> GetGeneralLogger();
    std::shared_ptr<spdlog::logger> GetHitLogger();
}

#endif