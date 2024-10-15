#ifndef KEY_HIT_H_
#define KEY_HIT_H_

#include <include/fftw3.h>

#include <fstream>
#include <vector>

namespace database::models {
class KeyHit {
   public:
    KeyHit(int hid, int elapsed_time, float pressure, bool is_big,
           bool is_special);
    KeyHit();
    int GetHid() const;
    std::vector<float> GetPressures();
    bool GetIsPressed() const;
    bool GetWasPressed() const;
    bool GetIsSpecial() const;
    bool GetIsBig() const;
    bool GetIsCalculated() const;
    int GetFirstTimeStamp() const;
    int GetDwellTime() const;
    double GetTotalEnergy() const;
    float GetMagnitude() const;
    void PushBackTimeStamp(int time_stamp);
    void PushBackPressure(float pressure);
    void SetHid(int hid);
    void SetIsSpecial(bool is_special);
    void SetIsBig(bool is_big);
    void SetDwellTime(int dwell_time);
    void SetTotalEnergy(double total_energy);
    void SetMagnitude(float magnitude);
    void SetIsPressed(bool is_special);
    void SetWasPressed(bool was_pressed);
    void SetIsCalculated(bool is_calculated);
    void UpdateKeyHit(int elapsed_time, float pressure);
    void Calculate();
    void SaveKeyHitToCsv(std::ofstream &file) const;
    void Interpolate();

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
    int hid_;
    int dwell_time_;
    double total_energy_;
    float magnitude_;

    void CalculateDwellTime();
    void CalculateDFTOfPressure();
    void CalculateMagnitude(fftw_complex *out, int size);
    void CalculateTotalEnergy(fftw_complex *out, int size);
};
}  // namespace database::models

#endif