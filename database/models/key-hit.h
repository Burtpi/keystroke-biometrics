#ifndef KEY_HIT_H_
#define KEY_HIT_H_

#include <include/fftw3.h>

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
    std::vector<float> pressures_interp_;
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

    void Interpolate();
    void CalculateDwellTime();
    void CalculateDFTOfPressure();
    void CalculateMagnitude(fftw_complex *out, int size);
    void CalculateTotalEnergy(fftw_complex *out, int size);
};
}  // namespace database::models

#endif