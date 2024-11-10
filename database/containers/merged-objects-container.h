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
    MergedObjectsContainer();
    MergedObjectsContainer(std::string container_name, std::string language)
        : name_(container_name), language_(language) {}
    void Sort();
    std::string GetName();
    std::string GetLanguage();
    void SetMergedObjects(std::vector<database::models::KeyHit>& key_hits,
                          std::vector<database::models::Ngraph>& ngraphs);

   private:
    std::string name_;
    std::string language_;
};
}  // namespace database::containers

#endif