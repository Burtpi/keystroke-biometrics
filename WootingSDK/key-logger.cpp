#include "key-logger.h"
#include "../Logger/logger.h"

wooting_sdk::KeyLogger::KeyLogger(int buffer_size)
{
    buffer_size_ = buffer_size;
    code_buffer_.resize(buffer_size);
    analog_buffer_.resize(buffer_size);
    Init();
}

void wooting_sdk::KeyLogger::Init()
{
    int initialised = wooting_analog_initialise();
    if (initialised >= 0)
    {
        is_initialised_ = true;
        logger::GetGeneralLogger()->info("Wooting Analog SDK initialised.");
    }
    else
    {
        logger::GetGeneralLogger()->error("Failed to initialise Wooting Analog SDK.");
    }
}