#ifndef CONFIG_MANAGER_H_
#define CONFIG_MANAGER_H_

#include "app-config.h"

namespace config
{
    class ConfigManager
    {
    public:
        AppConfig GetAppConfig();

    private:
        AppConfig app_config_;
    };

}

extern config::ConfigManager global_config;

#endif