#ifndef KEY_LOGGER_H_
#define KEY_LOGGER_H_

#include <models/key-buffer.h>

#include <vector>

#include "include/wooting-analog-wrapper.h"

namespace wooting_sdk {
class KeyLogger {
   public:
    KeyLogger(int buffer_size = 64);
    std::vector<KeyBuffer> ReadFullBuffer();

   private:
    int buffer_size_;
    std::vector<uint16_t> code_buffer_;
    std::vector<float> analog_buffer_;
    bool is_initialised_;

    void Init();
};
}  // namespace wooting_sdk

#endif