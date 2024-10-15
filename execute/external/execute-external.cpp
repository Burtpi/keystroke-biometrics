#include <config/config-manager.h>
#include <database/database.h>
#include <execute/external/execute-external.h>
#include <utils/biometric_template/utils-template.h>
#include <utils/calc/utils-calc.h>
#include <utils/key/utils-key.h>

void execute::external::RunExternal() {
    utils::key::LoadAllHits();
    if (global_config_manager.GetCalcConfig().GetIsTemplateInit()) {
        utils::biometric_template::CreateTemplate();
        utils::biometric_template::SaveToFile();
    } else {
        utils::calc::CalculateCurrentObjects();
        database_manager.GetTemplateContainer().LogScores();
    }
}