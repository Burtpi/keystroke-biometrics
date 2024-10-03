#include "app-config.h"

std::string config::AppConfig::GetStartDateString()
{
    return start_date_string_;
}

std::chrono::time_point<std::chrono::system_clock> config::AppConfig::GetStartDate()
{
    return start_date_;
}

bool config::AppConfig::GetKeyLogging()
{
    return key_logging_;
}

void config::AppConfig::SetKeyLogging(bool key_logging)
{
    key_logging_ = key_logging;
}

config::AppConfig::AppConfig()
{
    start_date_ = std::chrono::system_clock::now();
    key_logging_ = true;
}
