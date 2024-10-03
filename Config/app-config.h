#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <utils/time/utils-time.h>
#include <chrono>

namespace config
{
    class AppConfig
    {
    public:
        std::string GetStartDateString();
        std::chrono::time_point<std::chrono::system_clock> GetStartDate();
        bool GetKeyLogging();
        void SetKeyLogging(bool key_logging);
        AppConfig();

    private:
        std::chrono::time_point<std::chrono::system_clock> start_date_;
        std::string start_date_string_;
        bool key_logging_;
    };
}
#endif