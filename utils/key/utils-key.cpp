#include "utils-key.h"

std::vector<KeyBuffer> utils::key::SortKeyStates(std::vector<KeyBuffer> key_states)
{
    std::vector<KeyBuffer> sorted_key_states = key_states;
    std::sort(sorted_key_states.begin(), sorted_key_states.end());
    return sorted_key_states;
}