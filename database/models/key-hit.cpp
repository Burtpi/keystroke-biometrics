#include <database/models/key-hit.h>

database::models::KeyHit::KeyHit(int hid, int elapsed_time, float pressure,
                                 bool is_big, bool is_special) {
    hid_ = hid;
    time_stamps_.push_back(elapsed_time);
    pressures_.push_back(pressure);
    dwell_time_ = 0;
    flight_time_ = 0;
    total_energy_ = 0;
    is_pressed_ = true;
    is_calculated_ = false;
    is_special_char_ = is_special;
    is_big_char_ = is_big;
    is_interpolated_ = false;
}
int database::models::KeyHit::GetHid() const { return hid_; }
bool database::models::KeyHit::GetIsPressed() const { return is_pressed_; }
bool database::models::KeyHit::GetIsSpecial() { return is_special_char_; }
void database::models::KeyHit::PushBackTimeStamp(int time_stamp) {
    time_stamps_.push_back(time_stamp);
}
void database::models::KeyHit::PushBackPressure(float pressure) {
    pressures_.push_back(pressure);
}

void database::models::KeyHit::SetIsPressed(bool is_pressed) {
    is_pressed_ = is_pressed;
}

void database::models::KeyHit::SetIsCalculated(bool is_calculated) {
    is_calculated_ = is_calculated;
}

void database::models::KeyHit::SetIsInterpolated(bool is_interpolated) {
    is_interpolated_ = is_interpolated;
}

void database::models::KeyHit::SetIsPressed(bool is_pressed) {
    is_pressed_ = is_pressed;
}
