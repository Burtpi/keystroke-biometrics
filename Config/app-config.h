#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include "../Utils/utils.h"

namespace config
{
    class AppConfig
    {
    private:
        std::string current_date_;

    public:
        std::string GetCurrentDate();
        AppConfig();
    };
}
#endif