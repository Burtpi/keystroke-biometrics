#ifndef KEY_BUFFER_H_
#define KEY_BUFFER_H_

namespace database::models {
struct KeyBuffer {
    int hid;
    float pressure;

    KeyBuffer(int code_buffer, float analog_buffer)
        : hid(code_buffer), pressure(analog_buffer) {}

    bool operator<(const KeyBuffer &other) const {
        if (hid != other.hid) {
            return hid < other.hid;
        }
        return pressure < other.pressure;
    }
};

}  // namespace database::models

#endif