#include <config/config-manager.h>
#include <database/database.h>
#include <database/models/key-buffer.h>
#include <execute/logger/execute-logger.h>
#include <fmt/ranges.h>
#include <utils/biometric_template/utils-template.h>
#include <utils/calc/utils-calc.h>
#include <utils/key/utils-key.h>
#include <utils/key/validators/utils-key-validators.h>
#include <utils/time/utils-time.h>
#include <wooting_sdk/key-logger.h>

#include <vector>

void execute::logger::RunLogger() {
    wooting_sdk::KeyLogger key_logger;

    while (global_config_manager.GetAppConfig().GetKeyLogging()) {
        global_config_manager.GetAppConfig().SetElapsedTime();
        std::vector<database::models::KeyBuffer> key_states =
            key_logger.ReadFullBuffer();

        if (!key_states.empty()) {
            try {
                if (global_config_manager.GetAppConfig().GetKeyStatesLogging())
                    utils::key::LogKeyStates(key_states);

                for (database::models::KeyBuffer key_state : key_states) {
                    utils::key::validators::CheckIfExit(key_state);
                    utils::key::CreateKeyHits(key_state);
                    utils::key::validators::CheckIfKeyIsPressed(key_state);
                }
                utils::key::RemoveNotPressedHits();

                if (!global_config_manager.GetCalcConfig()
                         .GetIsTemplateInit()) {
                    utils::calc::CalculateCurrentObjects();
                    if (database_manager.GetKeyHitContainer()
                            .GetEntries()
                            .size() > 200) {
                        database_manager.GetTemplateContainer().LogScores();
                        break;
                    }
                }
            } catch (const std::exception &e) {
                global_config_manager.GetLoggerConfig()
                    .GetGeneralLogger()
                    ->error("Error occured {}", e.what());
            }
        }

        utils::time::SleepHighResolution();
    }
    utils::key::LogAllHits();

    if (global_config_manager.GetCalcConfig().GetIsTemplateInit()) {
        utils::biometric_template::CreateTemplate();
        utils::biometric_template::SaveToFile();
    }
}