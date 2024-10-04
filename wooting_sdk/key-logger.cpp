#include <logger/logger.h>
#include <wooting_sdk/key-logger.h>

wooting_sdk::KeyLogger::KeyLogger(int buffer_size) {
    buffer_size_ = buffer_size;
    code_buffer_.resize(buffer_size);
    analog_buffer_.resize(buffer_size);
    Init();
}

void wooting_sdk::KeyLogger::Init() {
    int initialised = wooting_analog_initialise();
    if (initialised >= 0) {
        is_initialised_ = true;
        logger::GetGeneralLogger()->info("Wooting Analog SDK initialised.");
    } else {
        logger::GetGeneralLogger()->error(
            "Failed to initialise Wooting Analog SDK.");
        exit(1);
    }
}

std::vector<database::models::KeyBuffer>
wooting_sdk::KeyLogger::ReadFullBuffer() {
    wooting_analog_read_full_buffer(&code_buffer_[0], &analog_buffer_[0],
                                    buffer_size_);

    std::vector<database::models::KeyBuffer> buffer;
    for (int i = 0; i < buffer_size_; i++) {
        if (code_buffer_[i] > 0) {
            buffer.emplace_back(code_buffer_[i], analog_buffer_[i]);
        }
    }
    code_buffer_ = std::vector<uint16_t>();
    code_buffer_.resize(buffer_size_);
    return buffer;
}
