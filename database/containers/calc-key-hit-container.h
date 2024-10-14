#ifndef CALC_KEY_HIT_CONTAINER_H_
#define CALC_KEY_HIT_CONTAINER_H_

#include <database/containers/container.h>
#include <database/models/calc-key-hit.h>
#include <database/models/key-hit.h>

#include <vector>

namespace database::containers {
class CalcKeyHitContainer : public Container<database::models::CalcKeyHit> {
   public:
    void AddEntry(std::tuple<int, bool, bool> key_hit,
                  std::vector<database::models::KeyHit> key_hit_data);
    void SaveToFile();
    void LoadFromFile(std::string csv_file_path);
    void GenerateCalcKeyHitHashMap();
    std::optional<database::models::CalcKeyHit> FindEntry(
        database::models::KeyHit key_hit) const;

   private:
    std::unordered_map<std::tuple<int, bool, bool>,
                       database::models::CalcKeyHit>
        calc_key_hit_hash_map;
};
}  // namespace database::containers

#endif