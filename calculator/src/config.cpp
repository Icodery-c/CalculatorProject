#include "config.h"

#include <fstream>
#include <stdexcept>
#include <sstream>

void Config::load(const std::string& path) {

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open config file: " + path);
    }

    std::string section;
    std::string line;

    while (std::getline(file, line)) {

        // Убираем пробелы по краям
        size_t start = line.find_first_not_of(" \t");
        if (start == std::string::npos) continue;
        line = line.substr(start);

        // Комментарии и пустые строки
        if (line.empty() || line[0] == '#' || line[0] == ';') continue;

        // Секция [name]
        if (line[0] == '[' && line.back() == ']') {
            section = line.substr(1, line.size() - 2);
            continue;
        }

        // Пара key=value
        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;

        std::string key   = line.substr(0, eq);
        std::string value = line.substr(eq + 1);

        // Полный ключ: section.key
        std::string fullKey = section.empty() ? key : section + "." + key;
        values[fullKey] = value;
    }
}

std::string Config::getString(const std::string& key, const std::string& defaultValue) const {
    auto it = values.find(key);
    return it != values.end() ? it->second : defaultValue;
}

int Config::getInt(const std::string& key, int defaultValue) const {
    auto it = values.find(key);
    if (it == values.end()) return defaultValue;
    try {
        return std::stoi(it->second);
    } catch (...) {
        return defaultValue;
    }
}