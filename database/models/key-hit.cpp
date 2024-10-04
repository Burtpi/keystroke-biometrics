#include <database/models/key-hit.h>

database::models::KeyHit::KeyHit(int hid) {
    hid_ = hid;
    dwell_time_ = 0;
    flight_time_ = 0;
    total_energy_ = 0;
    is_pressed_ = true;
    is_calculated_ = false;
    is_special_char_ = false;
    is_big_char_ = false;
    is_interpolated_ = false;
}
int database::models::KeyHit::GetHid() { return hid_; }
bool database::models::KeyHit::GetIsPressed() { return is_pressed_; }
void database::models::KeyHit::PushBackTimeStamp(int time_stamp) {
    time_stamps_.push_back(time_stamp);
}
void database::models::KeyHit::PushBackPressure(float pressure) {
    pressures_.push_back(pressure);
}