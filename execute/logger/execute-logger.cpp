#include <config/config-manager.h>
#include <execute/logger/execute-logger.h>
#include <models/key-buffer.h>
#include <utils/key/utils-key.h>
#include <utils/time/utils-time.h>
#include <wooting_sdk/key-logger.h>

#include <vector>

void execute::logger::RunLogger() {
    wooting_sdk::KeyLogger key_logger;

    while (global_config_manager.GetAppConfig().GetKeyLogging()) {
        std::vector<KeyBuffer> key_states = key_logger.ReadFullBuffer();

        if (!key_states.empty()) {
            if (global_config_manager.GetAppConfig().GetKeyStatesLogging())
                utils::key::LogKeyStates(key_states);
        }
        utils::time::SleepHighResolution();
    }
}