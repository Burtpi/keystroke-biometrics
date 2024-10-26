#ifndef MERGED_OBJECTS_CONTAINER_H_
#define MERGED_OBJECTS_CONTAINER_H_

#include <database/containers/container.h>
#include <database/models/key-hit.h>
#include <database/models/ngraph.h>

#include <variant>

namespace database::containers {
using MergedObjectsVariant =
    std::variant<database::models::KeyHit, database::models::Ngraph>;
class MergedObjectsContainer : public Container<MergedObjectsVariant> {
   public:
    void Sort();
};
}  // namespace database::containers

#endif