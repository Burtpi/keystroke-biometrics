#include <config/config-manager.h>
#include <database/containers/merged-objects-container.h>
#include <database/database.h>
#include <database/templates/template-container.h>
#include <execute/external/execute-external.h>
#include <utils/biometric_template/utils-template.h>
#include <utils/calc/utils-calc.h>
#include <utils/key/utils-key.h>
#include <utils/optimizer/utils-optimizer.h>

#include <iostream>

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

void execute::external::RunOptimize() {
    std::vector<database::templates::TemplateContainer> template_containers =
        utils::optimizer::LoadTemplatesWithNames();
    std::vector<database::containers::MergedObjectsContainer>
        merged_objects_containers = utils::optimizer::LoadAllOptimizationData();
}