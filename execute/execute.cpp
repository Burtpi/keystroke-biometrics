#include "execute.h"

#include <execute/external/execute-external.h>
#include <execute/logger/execute-logger.h>

void execute::Run() {
    if (global_config_manager.GetAppConfig().GetIsExternalTemplate()) {
        execute::external::RunExternal();
    } else {
        execute::logger::RunLogger();
    }
}