#ifndef CONFIG_MANAGER_H_
#define CONFIG_MANAGER_H_

#include <config/app-config.h>
#include <config/calc-config.h>
#include <config/language-config.h>
#include <config/logger-config.h>

namespace config {
class ConfigManager {
   public:
    AppConfig &GetAppConfig();
    const LanguageConfig &GetLanguageConfig() const;
    const CalcConfig &GetCalcConfig() const;
    LoggerConfig &GetLoggerConfig();
    bool ReadTerminalFlags(int argc, char *argv[]);

   private:
    AppConfig app_config_;
    LanguageConfig language_config_;
    CalcConfig calc_config_;
    LoggerConfig logger_config_;
    void DisplayHelp();
};

}  // namespace config

extern config::ConfigManager global_config_manager;

#endif