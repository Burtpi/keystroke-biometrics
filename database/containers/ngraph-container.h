#ifndef NGRAPH_CONTAINER_H_
#define NGRAPH_CONTAINER_H_

#include <config/config-manager.h>
#include <database/containers/container.h>
#include <database/models/ngraph.h>

#include <string>
#include <vector>

namespace database::containers {
class NgraphContainer : public Container<database::models::Ngraph> {
    // -----------------------------------------------------------
    // Inherits from container.h
    // Container for Ngraphs
    //
    // Changes:
    //  - AddEntry logic modified
    //  - SaveToFile and LoadFromFile used for reuse of calculated data
    // -----------------------------------------------------------
   public:
    void AddEntry(std::string ngraph, std::vector<int>& time_stamps);
    void SaveToFile();
    void LoadFromFile(
        std::string base_path =
            global_config_manager.GetAppConfig().GetExternalDataNgraphsPath());
};
}  // namespace database::containers

#endif