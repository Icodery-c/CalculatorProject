#include "runner.h"
#include "logger.h"

#include <exception>

void Runner::run(int argc, char** argv)
{
    auto& log = logger::Logger::Initialize();

    try
    {
        log.info("Starting calculator application");

        log.debug("Parsing input...");
        Data data = parser.parse(argc, argv);

        if (data.op == Operation::Help) { printer.printHelp(); return; }

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