#include <config/app-config.h>
#include <utils/time/utils-time.h>

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

bool config::AppConfig::GetOptimize() { return optimize_; }

void config::AppConfig::SetOptimize(bool optimize) { optimize_ = optimize; }

std::string config::AppConfig::GetExternalDataKeyHitsPath() {
    return external_data_key_hits_path_;
}

std::string config::AppConfig::GetExternalDataNgraphsPath() {
    return external_data_ngraphs_path_;
}

void config::AppConfig::SetExternalDataKeyHitsPath(std::string path) {
    external_data_key_hits_path_ = path;
}

void config::AppConfig::SetExternalDataNgraphsPath(std::string path) {
    external_data_ngraphs_path_ = path;
}

std::string config::AppConfig::GetElapsedTime() { return elapsed_time_; }

void config::AppConfig::SetElapsedTime() {
    elapsed_time_ = utils::time::CalculateElapsedTime();
}

int config::AppConfig::GetExitHid() { return exit_hid_; }

void config::AppConfig::SetExitHid(int hid) { exit_hid_ = hid; }

config::AppConfig::AppConfig(bool key_logging, bool key_sates_logging,
                             bool is_external_data_, int exit_hid) {
    key_logging_ = key_logging;
    key_states_logging_ = key_sates_logging;
    is_external_data_ = is_external_data_;
    exit_hid_ = exit_hid;
    elapsed_time_ = "";
    actuation_point_ = 0.4;
}
