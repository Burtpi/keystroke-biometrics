#include <key-logger.h>

WootingSDK::KeyLogger::KeyLogger(int buffer_size)
{
    buffer_size_ = buffer_size;
    code_buffer_.resize(buffer_size);
    analog_buffer_.resize(buffer_size);
    Init();
}

void WootingSDK::KeyLogger::Init()
{
    int initialised = wooting_analog_initialise();
    if (initialised >= 0)
    {
        is_initialised_ = true;
    }
    else
    {
        // std::cerr << "Failed to initialise Wooting Analog SDK." << std::endl;
    }
}