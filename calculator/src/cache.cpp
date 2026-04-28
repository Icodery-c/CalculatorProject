#include "cache.h"
#include <stdexcept>
#include <algorithm>
#include <unordered_map>

static const std::unordered_map<Operation, char> OPERATION_SYMBOLS = {
    {Operation::Add,       '+'},
    {Operation::Subtract,  '-'},
    {Operation::Multiply,  '*'},
    {Operation::Divide,    '/'},
    {Operation::Power,     '^'},
    {Operation::Factorial, '!'}
};

static char operationToSymbol(Operation op) {
    auto it = OPERATION_SYMBOLS.find(op);
    if (it == OPERATION_SYMBOLS.end()) {
        return '?';
    }
    return it->second;
}

std::string Cache::makeKey(const Data& data) {

    char opSymbol = operationToSymbol(data.op);

    // Для коммутативных операций сортируем числа чтобы "1+2" == "2+1"
    if (data.op == Operation::Add || data.op == Operation::Multiply) {
        int a = std::min(data.num1, data.num2);
        int b = std::max(data.num1, data.num2);
        return std::to_string(a) + opSymbol + std::to_string(b);
    }

    // Факториал — только num1
    if (data.op == Operation::Factorial) {
        return std::to_string(data.num1) + opSymbol;
    }
    
    // Остальные — порядок важен
    return std::to_string(data.num1) + opSymbol + std::to_string(data.num2);
}

bool Cache::contains(const std::string& key) const {
    return storage.find(key) != storage.end();
}

int Cache::get(const std::string& key) const {
    auto it = storage.find(key);
    if (it == storage.end()) {
        throw std::runtime_error("Key not found in cache: " + key);
    }
    return it->second;
}

void Cache::put(const std::string& key, int result) {
    storage[key] = result;
}
