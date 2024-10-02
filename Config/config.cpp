#include "config.h"

config::Config CONFIG;

std::string config::Config::GetCurrentDate()
{
    return current_date_;
}

config::Config::Config()
{
    current_date_ = utils::GetCurrentDate();
}
