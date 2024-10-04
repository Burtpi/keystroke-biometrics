#include <utils/key/utils-key.h>
#include <utils/time/utils-time.h>
#include <logger/logger.h>
#include <string>

std::vector<KeyBuffer> utils::key::SortKeyStates(std::vector<KeyBuffer> key_states)
{
    std::vector<KeyBuffer> sorted_key_states = key_states;
    std::sort(sorted_key_states.begin(), sorted_key_states.end());
    return sorted_key_states;
}

void utils::key::LogKeyStates(std::vector<KeyBuffer> key_states)
{
    std::vector<KeyBuffer> sorted_key_states = utils::key::SortKeyStates(key_states);
    std::string elapsed_time = utils::time::CalculateElapsedTime();

    std::stringstream row;

    row << "Elapsed Time: " << elapsed_time << ", Size: " << std::to_string(sorted_key_states.size()) << ", Keys: [";

    for (KeyBuffer key : sorted_key_states)
    {
        if (key.pressure > -1)
        {
            row << "{Key: " << key.hid << ", Pressure: " << key.pressure << "}, ";
        }
    }
    row << "]";
    logger::GetHitLogger()->info(row.str());
}