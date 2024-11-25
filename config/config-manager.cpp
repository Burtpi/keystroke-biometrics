#include <config/config-manager.h>

#include <fstream>
#include <iostream>

// Initializing manager for global use
config::ConfigManager global_config_manager;

config::AppConfig &config::ConfigManager::GetAppConfig() { return app_config_; }
const config::LanguageConfig &config::ConfigManager::GetLanguageConfig() const {
    return language_config_;
}

config::CalcConfig &config::ConfigManager::GetCalcConfig() {
    return calc_config_;
}

config::LoggerConfig &config::ConfigManager::GetLoggerConfig() {
    return logger_config_;
}

bool config::ConfigManager::ReadTerminalFlags(int argc, char *argv[]) {
    if (argc < 2) {
        return true;
    }
    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Reading flags from terminal.");
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
                DisplayHelp();
                return false;
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
            } else if (strcmp(argv[i], "-o") == 0 ||
                       strcmp(argv[i], "--optimize") == 0) {
                app_config_.SetOptimize(true);
            } else if (strcmp(argv[i], "-l") == 0 ||
                       strcmp(argv[i], "--language") == 0) {
                if (i + 1 < argc) {
                    i++;
                    bool is_set = language_config_.SetModelLanguage(argv[i]);
                    if (!is_set) {
                        std::cerr << "Language not found for " << argv[i]
                                  << " flag." << std::endl;
                        DisplayHelp();
                        return false;
                    }

                } else {
                    std::cerr << "Missing value for " << argv[i]
                              << " flag. Default is English." << std::endl;
                    DisplayHelp();
                    return false;
                }
            } else if (strcmp(argv[i], "-eh") == 0 ||
                       strcmp(argv[i], "--external-hits") == 0) {
                if (i + 1 < argc) {
                    i++;
                    app_config_.SetExternalDataKeyHitsPath(argv[i]);
                    std::ifstream file(argv[i]);
                    if (!file.good()) {
                        std::cerr << "File " << argv[i] << " not found."
                                  << std::endl;
                        DisplayHelp();
                        return false;
                    }
                    app_config_.SetIsExternalData(true);

                } else {
                    std::cerr << "Missing value for " << argv[i] << " flag."
                              << std::endl;
                    DisplayHelp();
                    return false;
                }
            } else if (strcmp(argv[i], "-en") == 0 ||
                       strcmp(argv[i], "--external-ngraphs") == 0) {
                if (i + 1 < argc) {
                    i++;
                    app_config_.SetExternalDataNgraphsPath(argv[i]);
                    std::ifstream file(argv[i]);
                    if (!file.good()) {
                        std::cerr << "File " << argv[i] << " not found."
                                  << std::endl;
                        DisplayHelp();
                        return false;
                    }
                    app_config_.SetIsExternalData(true);

                } else {
                    std::cerr << "Missing value for " << argv[i] << " flag."
                              << std::endl;
                    DisplayHelp();
                    return false;
                }
            } else {
                std::cout << "Option not found " << argv[i] << std::endl;
                DisplayHelp();
                return false;
            }
        } else {
            std::cout << "No option specified. " << argv[i] << std::endl;
            DisplayHelp();
            return false;
        }
    }
    global_config_manager.GetLoggerConfig().GetGeneralLogger()->info(
        "Successfully read the flags from the terminal.");
    return true;
}

void config::ConfigManager::DisplayHelp() {
    std::cout << "Usage: .\\keystroke_biometrics.exe [OPTIONS]\n";
    std::cout << "Options:\n";
    std::cout << "  -h or --help\t\t\t\t Display this help message.\n";
    std::cout
        << "  --no-logs\t\t\t\t Logs from hit logger will not be saved.\n";
    std::cout << "  -nn or --no-ngraph\t\t\t Ngraph feature will not be "
                 "calculated in identification and verification scenario.\n";
    std::cout << "  -nd or --no-dwell\t\t\t Dwell Time feature will not be "
                 "calculated in identification and verification scenario.\n";
    std::cout << "  -np or --no-pressure\t\t\t Pressure feature will not be "
                 "calculated in identification and verification scenario.\n";
    std::cout << "  -i or --init\t\t\t\t Create template with your keystroke "
                 "dynamics biometrics features.\n";
    std::cout << "  -o or --optimize\t\t\t\t Optimize weights for descriptors "
                 "with Particle Swarm Optimization.\n";
    std::cout << "  -l <arg> or --language <arg>\t\t Choose language that will "
                 "be used in evaluation. It needs languages directory with "
                 "it's corresponding language given as argument. Default is "
                 "'en' (English).\n";
    std::cout << "  -en <arg> or --external-ngraph <arg>\t Choose external "
                 "file with ngraphs that will "
                 "be used in evaluation.\n";
    std::cout << "  -eh <arg> or --external-hits <arg>\t Choose external "
                 "file with key hits that will "
                 "be used in evaluation.\n";
    std::cout << "Example:\n";
    std::cout << "  .\\keystroke_biometrics.exe --language pl\n";
}