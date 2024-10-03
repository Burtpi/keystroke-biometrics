#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include "../Utils/utils.h"

namespace config
{
    class AppConfig
    {
    public:
        std::string GetCurrentDate();
        AppConfig();

    private:
        std::string current_date_;
    };
}
#endif