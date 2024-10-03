struct KeyBuffer
{
    int code_buffer;
    float analog_buffer;

    KeyBuffer(int code_buffer, float analog_buffer) : code_buffer(code_buffer), analog_buffer(analog_buffer) {}
};