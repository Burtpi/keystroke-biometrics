#include <config/config-manager.h>
#include <database/containers/merged-objects-container.h>

#include <algorithm>

database::containers::MergedObjectsContainer::MergedObjectsContainer() {}

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

std::string database::containers::MergedObjectsContainer::GetName() {
    return name_;
}

std::string database::containers::MergedObjectsContainer::GetLanguage() {
    return language_;
}

void database::containers::MergedObjectsContainer::SetLanguage() {
    language_ = global_config_manager.GetLanguageConfig().GetModelLanguage();
}

void database::containers::MergedObjectsContainer::SetMergedObjects(
    std::vector<database::models::KeyHit>& key_hits,
    std::vector<database::models::Ngraph>& ngraphs) {
    // Merge KeyHit and Ngraph containers
    entries_.insert(entries_.end(), key_hits.begin(), key_hits.end());
    entries_.insert(entries_.end(), ngraphs.begin(), ngraphs.end());
}