#ifndef LANGUAGE_H_
#define LANGUAGE_H_

#include <map>
#include <string>
#include <vector>

namespace models
{
    std::map<int, std::string> hid_to_ascii;

    struct Language
    {
        std::map<int, std::string> special_chars_ascii;
        std::vector<std::string> digraph;
        std::vector<std::string> trigraph;
    };
}

#endif