#ifndef KEY_LOGGER_H_
#define KEY_LOGGER_H_

#include <database/models/key-buffer.h>
#include <include/wooting-analog-wrapper.h>

#include <vector>

namespace wooting_sdk {
class KeyLogger {
    // -----------------------------------------------------------
    // KeyLogger class based on Wooting SDK for Analog keyboards
    // https://github.com/WootingKb/wooting-analog-sdk
    //
    // Used to acquire data about pressed keys (hid, pressure) from the
    // keyboard's buffer
    // -----------------------------------------------------------
   public:
    KeyLogger(int buffer_size = 64);
    std::vector<database::models::KeyBuffer> ReadFullBuffer();

   private:
    int buffer_size_;
    std::vector<uint16_t> code_buffer_;
    std::vector<float> analog_buffer_;
    bool is_initialised_;

    void Init();
};
}  // namespace wooting_sdk

#endif