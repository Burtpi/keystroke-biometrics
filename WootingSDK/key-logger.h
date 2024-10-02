#ifndef KEY_LOGGER_H_
#define KEY_LOGGER_H_

#include <vector>
#include <include/wooting-analog-wrapper.h>

namespace wooting_sdk
{
    class KeyLogger
    {
    private:
        int buffer_size_;
        std::vector<uint16_t> code_buffer_;
        std::vector<float> analog_buffer_;
        bool is_initialised_;

        void Init();

    public:
        KeyLogger(int buffer_size = 64);
    };
}

#endif