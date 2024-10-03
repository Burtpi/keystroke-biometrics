#include "app-config.h"

std::string config::AppConfig::GetCurrentDate()
{
    return current_date_;
}

config::AppConfig::AppConfig()
{
    current_date_ = utils::GetCurrentDate();
}
