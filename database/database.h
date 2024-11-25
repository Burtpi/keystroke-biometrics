#ifndef DATABASE_H_
#define DATABASE_H_

#include <database/containers/calc-key-hit-container.h>
#include <database/containers/calc-ngraph-container.h>
#include <database/containers/container.h>
#include <database/containers/key-hit-container.h>
#include <database/containers/merged-objects-container.h>
#include <database/containers/ngraph-container.h>
#include <database/templates/template-container.h>

namespace database {
class DatabaseManager {
    // -----------------------------------------------------------
    // Database manager used for easier access to all of the available
    // containers
    // -----------------------------------------------------------
   public:
    database::containers::KeyHitContainer& GetKeyHitContainer();
    database::containers::NgraphContainer& GetNgraphContainer();
    database::containers::CalcKeyHitContainer& GetCalcKeyHitContainer();
    database::containers::CalcNgraphContainer& GetCalcNgraphContainer();
    database::containers::KeyHitContainer& GetModifierKeyHitContainer();
    database::containers::MergedObjectsContainer& GetMergedObjectsContainer();
    database::templates::TemplateContainer& GetTemplateContainer();

   private:
    database::containers::KeyHitContainer key_hit_container_;
    database::containers::NgraphContainer ngraph_container_;
    database::containers::CalcKeyHitContainer calc_key_hit_container_;
    database::containers::CalcNgraphContainer calc_ngraph_container_;
    database::containers::KeyHitContainer modifier_key_hit_container_;
    database::containers::MergedObjectsContainer merged_objects_container_;
    database::templates::TemplateContainer template_container_;
};
}  // namespace database

extern database::DatabaseManager database_manager;

#endif