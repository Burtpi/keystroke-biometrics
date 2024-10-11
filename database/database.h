#ifndef DATABASE_H_
#define DATABASE_H_

#include <database/containers/calc-key-hit-container.h>
#include <database/containers/calc-ngraph-container.h>
#include <database/containers/container.h>
#include <database/containers/key-hit-container.h>
#include <database/containers/ngraph-container.h>

namespace database {
class DatabaseManager {
   public:
    database::containers::KeyHitContainer GetKeyHitContainer() const;
    database::containers::NgraphContainer GetNgraphContainer() const;
    database::containers::CalcKeyHitContainer GetCalcKeyHitContainer() const;
    database::containers::CalcNgraphContainer GetCalcNgraphContainer() const;
    database::containers::KeyHitContainer GetModifierKeyHitContainer() const;

   private:
    database::containers::KeyHitContainer key_hit_container_;
    database::containers::NgraphContainer ngraph_container_;
    database::containers::CalcKeyHitContainer calc_key_hit_container_;
    database::containers::CalcNgraphContainer calc_ngraph_container_;
    database::containers::KeyHitContainer modifier_key_hit_container_;
};
}  // namespace database

extern database::DatabaseManager database_manager;

#endif