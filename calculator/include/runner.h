#pragma once

#include "parser.h"
#include "checker.h"
#include "calculator.h"
#include "printer.h"
#include "cache.h"
#include "database.h"
#include "server.h"

#include <memory>

class Runner {

    Parser parser;
    Checker checker;
    Calculator calculator;
    Printer printer;
    Cache cache;
    std::unique_ptr<database::Database> db;
    std::unique_ptr<server::Server> srv;

    std::string handleRequest(const std::string& request);

    public: 
        Runner();
        ~Runner() = default;

        Runner(const Runner&)            = delete;
        Runner& operator=(const Runner&) = delete;

        Runner(Runner&&)            = default;
        Runner& operator=(Runner&&) = default;

        void run();

        void stop();

};