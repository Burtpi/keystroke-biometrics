#include <utils/key/validators/utils-key-validators.h>

void utils::key::validators::CheckIfExit(std::vector<KeyBuffer> key_states)
{
    for (KeyBuffer key : key_states)
    {
        if (key.hid == global_config_manager.GetAppConfig().GetExitHid())
            global_config_manager.GetAppConfig().SetKeyLogging(false);
    }
}