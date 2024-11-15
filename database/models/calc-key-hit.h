#ifndef CALC_KEY_HIT_H_
#define CALC_KEY_HIT_H_

#include <database/models/key-hit.h>
#include <database/models/statistics.h>

#include <fstream>
#include <vector>

namespace database::models {
class CalcKeyHit {
    // -----------------------------------------------------------
    // Model for KeyHit templates
    // Used by CalcKeyHitContainer
    //
    // Data about each key's (hid, is_special, is_big) descriptors is
    // stored for calculation in the identification scenario
    //
    // For each of the descriptors, the mean and standard deviation are stored
    // -----------------------------------------------------------
   public:
    CalcKeyHit();
    CalcKeyHit(std::tuple<int, bool, bool> key_hit,
               std::vector<KeyHit>& key_hit_data);
    CalcKeyHit(std::vector<std::string> row);
    void SaveCalcKeyHitToCsv(std::ofstream& file);
    int GetHid();
    bool GetIsSpecial();
    bool GetIsBig();
    database::models::Statistics GetDwellTime();
    database::models::Statistics GetTotalEnergy();
    database::models::Statistics GetMagnitude();

   private:
    int hid_;
    bool is_special_;
    bool is_big_;
    database::models::Statistics dwell_time_;
    database::models::Statistics total_energy_;
    database::models::Statistics magnitude_;
    void Calculate(std::vector<KeyHit>& key_hit_data);
};
}  // namespace database::models

#endif