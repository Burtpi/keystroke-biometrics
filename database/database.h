#ifndef DATABASE_H_
#define DATABASE_H_

#include <database/containers/key-hit-container.h>
#include <database/containers/ngraph-container.h>

namespace database {
class DatabaseManager {
   public:
    database::containers::KeyHitContainer GetKeyHitContainer() const;
    const database::containers::NgraphContainer &GetNgraphContainer() const;

   private:
    database::containers::KeyHitContainer key_hit_container_;
    database::containers::NgraphContainer ngraph_container_;
};
}  // namespace database

extern database::DatabaseManager database_manager;

#endif