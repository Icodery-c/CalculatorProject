#include "runner.h"
#include "parser.h"
#include "checker.h"
#include "calculator.h"
#include "printer.h"
#include "logger.h"

#include <exception>

void Runner::run(int argc, char** argv)
{
    Parser parser;
    Checker checker;
    Calculator calculator;
    Printer printer;

    auto& log = logger::Logger::Initialize();

    try
    {

        log.info("Starting calculator application");

        log.debug("Parsing input...");
        Data data = parser.parse(argc, argv);

        if (data.op == 'h') { printer.printHelp(); return; }

        log.debug("Validating data...");
        checker.check(data);

        log.debug("Calculating...");
        int result = calculator.calculate(data);

        log.info("Result: " + std::to_string(result));
        printer.printResult(result);
    
    } catch (const std::exception& e) {

        log.error(std::string("Unexpected error: ") + e.what());
        printer.printError(e.what());
    }
}