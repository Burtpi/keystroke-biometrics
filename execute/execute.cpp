#include <config/config-manager.h>
#include <database/database.h>
#include <execute/execute.h>
#include <execute/external/execute-external.h>
#include <execute/logger/execute-logger.h>

void execute::Run() {
    if (!global_config_manager.GetCalcConfig().GetIsTemplateInit() &&
        !global_config_manager.GetAppConfig().GetOptimize()) {
        // Load templates for identification scenario
        database_manager.GetTemplateContainer().LoadTemplates("templates");
    }

    if (global_config_manager.GetAppConfig().GetOptimize()) {
        // Optimize weights for descriptors
        execute::external::RunOptimize();
    } else if (global_config_manager.GetAppConfig().GetIsExternalData()) {
        // Use old data for template creation or identification
        execute::external::RunExternal();
    } else {
        // Get new data
        execute::logger::RunLogger();
    }
}