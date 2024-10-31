#include <database/database.h>
#include <execute/execute.h>
#include <execute/external/execute-external.h>
#include <execute/logger/execute-logger.h>

#include <iostream>

void execute::Run() {
    if (!global_config_manager.GetCalcConfig().GetIsTemplateInit() &&
        !global_config_manager.GetAppConfig().GetOptimize()) {
        database_manager.GetTemplateContainer().LoadTemplates("templates");
    }

    if (global_config_manager.GetAppConfig().GetOptimize()) {
        execute::external::RunOptimize();
    } else if (global_config_manager.GetAppConfig().GetIsExternalData()) {
        execute::external::RunExternal();
    } else {
        execute::logger::RunLogger();
    }
}