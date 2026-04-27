#pragma once

#include "parser.h"
#include "checker.h"
#include "calculator.h"
#include "printer.h"
#include "cache.h"
#include "database.h"
#include <memory>

class Runner {

    Parser parser;
    Checker checker;
    Calculator calculator;
    Printer printer;
    Cache cache;
    std::unique_ptr<database::Database> db;

    public:

        Runner();
        ~Runner() = default;

        Runner(const Runner&)            = delete;
        Runner& operator=(const Runner&) = delete;

        Runner(Runner&&)            = default;
        Runner& operator=(Runner&&) = default;

        void run(int argc, char** argv);
};