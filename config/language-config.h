#ifndef LANGUAGE_CONFIG_H_
#define LANGUAGE_CONFIG_H_

#include <map>
#include <optional>
#include <string>
#include <vector>

namespace config {
class LanguageConfig {
    // -----------------------------------------------------------
    // Part of config-manager.h
    // Config used for easier access to n-graphs and characters
    // -----------------------------------------------------------
   public:
    LanguageConfig(std::string model_language = "en");
    const std::map<int, std::string>& GetHidToAscii() const;
    const std::map<int, std::string>& GetSpecialCharsAscii() const;
    const std::map<int, std::string>& GetModifierKeys() const;
    const std::vector<std::string>& GetDigraph() const;
    const std::vector<std::string>& GetTrigraph() const;
    const std::string& GetModelLanguage() const;
    bool SetModelLanguage(std::string model_language);

   private:
    std::string model_language_;
    std::map<int, std::string> hid_to_ascii_;
    std::map<int, std::string> modifier_keys_ascii_;
    std::map<int, std::string> special_chars_ascii_;
    std::vector<std::string> digraph_;
    std::vector<std::string> trigraph_;

    std::map<int, std::string> SetHidToAscii();
    std::map<int, std::string> SetModifierKeys();
    std::vector<std::string> SetDigraph();
    std::vector<std::string> SetTrigraph();
    std::optional<std::vector<std::string>> ReadNgraph(std::string ngraph_path);
    std::optional<std::map<int, std::string>> ReadSpecial();
};
}  // namespace config

#endif