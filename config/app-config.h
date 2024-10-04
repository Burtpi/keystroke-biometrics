#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <chrono>

namespace config
{
    class AppConfig
    {
    public:
        std::chrono::time_point<std::chrono::system_clock> GetStartDate();
        bool GetKeyLogging();
        void SetKeyLogging(bool key_logging);
        bool GetKeyStatesLogging();
        void SetKeyStatesLogging(bool key_states_logging);
        bool GetIsExternalTemplate();
        void SetIsExternalTemplate(bool is_external_template);
        int GetExitHid();
        void SetExitHid(int hid);
        AppConfig(bool key_logging = true, bool key_sates_logging = true, bool is_external_template = false, int exit_hid = 41);

    private:
        std::chrono::time_point<std::chrono::system_clock> start_date_;
        std::string start_date_string_;
        bool key_logging_;
        bool key_states_logging_;
        bool is_external_template_;
        int exit_hid_;
    };
}
#endif