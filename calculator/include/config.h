#pragma once

#include <string>
#include <unordered_map>

class Config {

    std::unordered_map<std::string, std::string> values;

    public:
    
        Config() = default;
        ~Config() = default;

        Config(const Config&)            = default;
        Config& operator=(const Config&) = default;

        Config(Config&&)            = default;
        Config& operator=(Config&&) = default;

        void load(const std::string& path);

        std::string getString(const std::string& key, const std::string& defaultValue = "") const;
        int         getInt(const std::string& key, int defaultValue = 0) const;

};