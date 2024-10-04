#include "app-config.h"

std::chrono::time_point<std::chrono::system_clock> config::AppConfig::GetStartDate() { return start_date_; }

bool config::AppConfig::GetKeyLogging() { return key_logging_; }

void config::AppConfig::SetKeyLogging(bool key_logging) { key_logging_ = key_logging; }

bool config::AppConfig::GetKeyStatesLogging() { return key_states_logging_; }

void config::AppConfig::SetKeyStatesLogging(bool key_states_logging) { key_states_logging_ = key_states_logging; }

bool config::AppConfig::GetIsExternalTemplate() { return is_external_template_; }

void config::AppConfig::SetIsExternalTemplate(bool is_external_template) { is_external_template_ = is_external_template; }

int config::AppConfig::GetExitHid() { return exit_hid_; }

void config::AppConfig::SetExitHid(int hid) { exit_hid_ = hid; }

config::AppConfig::AppConfig(bool key_logging, bool key_sates_logging, bool is_external_template, int exit_hid)
{
    start_date_ = std::chrono::system_clock::now();
    key_logging_ = key_logging;
    key_states_logging_ = key_sates_logging;
    is_external_template_ = is_external_template;
    exit_hid_ = exit_hid;
}
