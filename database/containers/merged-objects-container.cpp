#include <database/containers/merged-objects-container.h>

#include <algorithm>

void database::containers::MergedObjectsContainer::Sort() {
    std::sort(entries_.begin(), entries_.end(),
              [](const database::containers::MergedObjectsVariant& a,
                 const database::containers::MergedObjectsVariant& b) {
                  auto get_time_stamp = [](const auto& obj) {
                      return obj.GetTimeStamp();
                  };
                  return std::visit(get_time_stamp, a) <
                         std::visit(get_time_stamp, b);
              });
}