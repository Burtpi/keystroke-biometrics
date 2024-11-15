#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

#include <chrono>
#include <string>

namespace config {
class AppConfig {
    // -----------------------------------------------------------
    // Part of config-manager.h
    // Config used for evaluating execution of the program
    // -----------------------------------------------------------
   public:
    int GetActuationPoint();
    bool GetKeyLogging();
    void SetKeyLogging(bool key_logging);
    bool GetKeyStatesLogging();
    void SetKeyStatesLogging(bool key_states_logging);
    bool GetIsExternalData();
    void SetIsExternalData(bool is_external_data);
    bool GetOptimize();
    void SetOptimize(bool optimize);
    std::string GetExternalDataKeyHitsPath();
    std::string GetExternalDataNgraphsPath();
    void SetExternalDataKeyHitsPath(std::string path);
    void SetExternalDataNgraphsPath(std::string path);
    std::string GetElapsedTime();
    void SetElapsedTime();
    int GetExitHid();
    void SetExitHid(int hid);
    AppConfig(bool key_logging = true, bool key_sates_logging = true,
              bool is_external_data_ = false, int exit_hid = 41);

   private:
    bool key_logging_;
    bool key_states_logging_;
    bool is_external_data_;
    bool optimize_;
    std::string external_data_key_hits_path_;
    std::string external_data_ngraphs_path_;
    int exit_hid_;
    std::string elapsed_time_;
    float actuation_point_;
};
}  // namespace config
#endif