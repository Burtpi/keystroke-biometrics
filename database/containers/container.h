#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>

namespace database::containers {
template <typename T>
class Container {
   public:
    std::vector<T>& GetEntries() { return entries_; }
    void AddEntry(T entry) { entries_.emplace_back(entry); }
    std::vector<T>::const_iterator RemoveEntry(
        std::vector<T>::const_iterator entry) {
        return entries_.erase(entry);
    }

   protected:
    std::vector<T> entries_;
};
}  // namespace database::containers

#endif