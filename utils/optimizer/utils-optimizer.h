#ifndef UTILS_OPTIMIZER_H_
#define UTILS_OPTIMIZER_H_

#include <database/containers/merged-objects-container.h>
#include <database/templates/template-container.h>

#include <vector>

namespace utils::optimizer {
std::vector<database::templates::TemplateContainer> LoadTemplatesWithNames();
std::vector<database::containers::MergedObjectsContainer>
LoadAllOptimizationData();
database::containers::MergedObjectsContainer LoadAllOptimizationMergedData(
    std::string base_path, std::string name);
}  // namespace utils::optimizer

#endif