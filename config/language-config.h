#ifndef LANGUAGE_CONFIG_H_
#define LANGUAGE_CONFIG_H_

#include <map>
#include <string>
#include <vector>

namespace config {
class LanguageConfig {
   public:
    LanguageConfig(std::string model_language = "PL");
    const std::map<int, std::string>& GetHidToAscii() const;
    const std::map<int, std::string>& GetSpecialCharsAscii() const;
    const std::map<int, std::string>& GetModifierKeys() const;
    const std::vector<std::string>& GetDigraph() const;
    const std::vector<std::string>& GetTrigraph() const;

   private:
    std::string model_language_;
    std::map<int, std::string> hid_to_ascii_;
    std::map<int, std::string> modifier_keys_ascii_;
    std::map<int, std::string> special_chars_ascii_;
    std::vector<std::string> digraph_;
    std::vector<std::string> trigraph_;

    std::map<int, std::string> SetHidToAscii();
    std::map<int, std::string> SetModifierKeys();
    std::map<int, std::string> SetSpecialCharsAscii();
    std::vector<std::string> SetDigraph();
    std::vector<std::string> SetTrigraph();
};
}  // namespace config

#endif