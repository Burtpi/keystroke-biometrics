#ifndef KEY_HIT_H_
#define KEY_HIT_H_

#include <vector>

namespace database::models {
class KeyHit {
   public:
    KeyHit(int hid, int elapsed_time, float pressure, bool is_big,
           bool is_special);
    int GetHid() const;
    std::vector<float> GetPressures();
    bool GetIsPressed() const;
    bool GetWasPressed() const;
    bool GetIsSpecial();
    void PushBackTimeStamp(int time_stamp);
    void PushBackPressure(float pressure);
    void SetIsPressed(bool is_special);
    void SetWasPressed(bool was_pressed);
    void SetIsCalculated(bool is_calculated);
    void SetIsInterpolated(bool is_interpolated);
    void Calculate();

   private:
    std::vector<int> time_stamps_;
    std::vector<float> pressures_;
    std::vector<int> time_stamps_interp_;
    std::vector<float> pressure_interp_;
    bool is_special_char_;
    bool was_pressed_;
    bool is_pressed_;
    bool is_big_char_;
    bool is_calculated_;
    bool is_interpolated_;
    int hid_;
    int dwell_time_;
    int flight_time_;
    double total_energy_;
    float magnitude_;

    void CalculateDwellTime();
    void CalcualteFlightTime();
    void CalculateDFTOfPressure();
    void CalculateMagnitude();
    void CalculateTotalEnergy();
};
}  // namespace database::models

#endif