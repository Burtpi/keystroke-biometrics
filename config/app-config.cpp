#include <config/app-config.h>
#include <utils/time/utils-time.h>

std::chrono::time_point<std::chrono::system_clock>
config::AppConfig::GetStartDate() {
    return start_date_;
}

int config::AppConfig::GetActuationPoint() { return actuation_point_; }

bool config::AppConfig::GetKeyLogging() { return key_logging_; }

void config::AppConfig::SetKeyLogging(bool key_logging) {
    key_logging_ = key_logging;
}

bool config::AppConfig::GetKeyStatesLogging() { return key_states_logging_; }

void config::AppConfig::SetKeyStatesLogging(bool key_states_logging) {
    key_states_logging_ = key_states_logging;
}

bool config::AppConfig::GetIsExternalData() { return is_external_data_; }

void config::AppConfig::SetIsExternalData(bool is_external_data) {
    is_external_data_ = is_external_data;
}

std::string config::AppConfig::GetElapsedTime() { return elapsed_time_; }

void config::AppConfig::SetElapsedTime() {
    elapsed_time_ = utils::time::CalculateElapsedTime();
}

int config::AppConfig::GetExitHid() { return exit_hid_; }

void config::AppConfig::SetExitHid(int hid) { exit_hid_ = hid; }

config::AppConfig::AppConfig(bool key_logging, bool key_sates_logging,
                             bool is_external_template, int exit_hid) {
    start_date_ = std::chrono::system_clock::now();
    key_logging_ = key_logging;
    key_states_logging_ = key_sates_logging;
    is_external_template_ = is_external_template;
    exit_hid_ = exit_hid;
    elapsed_time_ = "";
    actuation_point_ = 0.4;
}
