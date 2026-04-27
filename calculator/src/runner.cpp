#include "runner.h"
#include "logger.h"

#include <exception>
#include <string>

static const std::string CONNECTION_STRING =
    "host=localhost dbname=calculator_db user=calculator password=calculator";

static std::string operationToName(Operation op) {
    switch (op) {
        case Operation::Add:       return "Add";
        case Operation::Subtract:  return "Subtract";
        case Operation::Multiply:  return "Multiply";
        case Operation::Divide:    return "Divide";
        case Operation::Power:     return "Power";
        case Operation::Factorial: return "Factorial";
        default:                   return "Unknown";
    }
}

Runner::Runner() : db(std::make_unique<database::Database>(CONNECTION_STRING)) {

    auto& log = logger::Logger::Initialize();

    log.debug("Warming up cache from database...");

    auto records = db->loadAllOperations();
    for (const auto& record : records) {
        Data data;
        data.num1 = record.num1;
        data.num2 = record.num2;

        if      (record.operation == "Add")       data.op = Operation::Add;
        else if (record.operation == "Subtract")  data.op = Operation::Subtract;
        else if (record.operation == "Multiply")  data.op = Operation::Multiply;
        else if (record.operation == "Divide")    data.op = Operation::Divide;
        else if (record.operation == "Power")     data.op = Operation::Power;
        else if (record.operation == "Factorial") data.op = Operation::Factorial;
        else continue;

        if (record.status == 0) {
            cache.put(Cache::makeKey(data), record.result);
        }
    }

    log.info("Cache warmed up with " + std::to_string(records.size()) + " records");
}

void Runner::run(int argc, char** argv) {

    auto& log = logger::Logger::Initialize();

    try {
        log.info("Starting calculator application");

        log.debug("Parsing input...");
        Data data = parser.parse(argc, argv);

        if (data.op == Operation::Help) {
            printer.printHelp();
            return;
        }

        log.debug("Validating data...");
        checker.check(data);

        std::string key = Cache::makeKey(data);

        if (cache.contains(key)) {
            log.info("Cache hit for key: " + key);
            int result = cache.get(key);
            printer.printResult(result);
            return;
        }

        log.debug("Cache miss, calculating...");

        int result = 0;
        int status = 0;
        try {
            result = calculator.calculate(data);
        } catch (const std::exception& e) {
            status = 1;
            log.warn(std::string("Calculation failed: ") + e.what());

            database::OperationRecord record;
            record.num1      = data.num1;
            record.num2      = data.num2;
            record.operation = operationToName(data.op);
            record.result    = 0;
            record.status    = status;
            record.hasNum2   = (data.op != Operation::Factorial);
            db->saveOperation(record);

            throw;
        }

        cache.put(key, result);

        database::OperationRecord record;
        record.num1      = data.num1;
        record.num2      = data.num2;
        record.operation = operationToName(data.op);
        record.result    = result;
        record.status    = 0;
        record.hasNum2   = (data.op != Operation::Factorial);
        db->saveOperation(record);

        log.info("Result: " + std::to_string(result));
        printer.printResult(result);

    } catch (const std::exception& e) {

        log.error(std::string("Error: ") + e.what());
        printer.printError(e.what());
    }
}