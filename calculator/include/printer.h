#pragma once

#include "data.h"
#include <string>

class Printer {

public:
    Printer() = default;
    ~Printer() = default;

    Printer(const Printer&) = default;
    Printer& operator=(const Printer&) = default;

    Printer(Printer&&) = default;
    Printer& operator=(Printer&&) = default;

    void printResult(int result);
    void printError(const std::string& msg);
    void printHelp();
};