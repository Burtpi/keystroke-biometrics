#include <config/config-manager.h>

#include <iostream>

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

bool config::ConfigManager::ReadTerminalFlags(int argc, char *argv[]) {
    if (argc < 2) {
        return true;
    }

    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
                std::cout << "Help: This is a sample help message."
                          << std::endl;
            } else if (strcmp(argv[i], "--no-logs") == 0) {
                app_config_.SetKeyLogging(false);
            } else if (strcmp(argv[i], "-nn") == 0 ||
                       strcmp(argv[i], "--no-ngraph") == 0) {
                calc_config_.SetNgraph(false);
            } else if (strcmp(argv[i], "-nd") == 0 ||
                       strcmp(argv[i], "--no-dwell") == 0) {
                calc_config_.SetDwellTime(false);
            } else if (strcmp(argv[i], "-np") == 0 ||
                       strcmp(argv[i], "--no-pressure") == 0) {
                calc_config_.SetPressure(false);
            } else if (strcmp(argv[i], "-i") == 0 ||
                       strcmp(argv[i], "--init") == 0) {
                calc_config_.SetIsTemplateInit(true);
            } else if (strcmp(argv[i], "-l") == 0 ||
                       strcmp(argv[i], "--language") == 0) {
                if (i + 1 < argc) {
                    i++;
                    bool is_set = language_config_.SetModelLanguage(argv[i]);
                    if (!is_set) {
                        std::cerr << "Language not found for " << argv[i]
                                  << " flag." << std::endl;
                        return false;
                    }

                } else {
                    std::cerr << "Missing value for " << argv[i]
                              << " flag. Default is English." << std::endl;
                    return false;
                }
            } else {
                std::cout << "Option not found " << argv[i] << std::endl;
                return false;
            }
        }
    }
    return true;
}