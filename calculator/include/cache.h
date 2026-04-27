#pragma once

#include <string>
#include <unordered_map>
#include "data.h"

class Cache {

    std::unordered_map<std::string, int> storage;

public:
    Cache() = default;
    ~Cache() = default;

    Cache(const Cache&)            = default;
    Cache& operator=(const Cache&) = default;

    Cache(Cache&&)            = default;
    Cache& operator=(Cache&&) = default;

    static std::string makeKey(const Data& data);

    bool contains(const std::string& key) const;
    int get(const std::string& key) const;
    void put(const std::string& key, int result);
};
