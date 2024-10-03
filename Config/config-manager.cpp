#include "config-manager.h"

config::ConfigManager global_config;

config::AppConfig &config::ConfigManager::GetAppConfig()
{
    return app_config_;
}