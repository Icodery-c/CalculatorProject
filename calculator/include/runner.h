#pragma once

#include "parser.h"
#include "checker.h"
#include "calculator.h"
#include "printer.h"

class Runner {

    Parser parser;
    Checker checker;
    Calculator calculator;
    Printer printer;

public:
    Runner() = default;
    ~Runner() = default;

    Runner(const Runner&) = default;
    Runner& operator=(const Runner&) = default;

    Runner(Runner&&) = default;
    Runner& operator=(Runner&&) = default;

    void run(int argc, char** argv);
};