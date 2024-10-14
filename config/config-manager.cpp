#include <config/config-manager.h>

config::ConfigManager global_config_manager;

config::AppConfig &config::ConfigManager::GetAppConfig() { return app_config_; }
const config::LanguageConfig &config::ConfigManager::GetLanguageConfig() const {
    return language_config_;
}

const config::CalcConfig &config::ConfigManager::GetCalcConfig() const {
    return calc_config_;
}

config::LoggerConfig &config::ConfigManager::GetLoggerConfig() {
    return logger_config_;
}